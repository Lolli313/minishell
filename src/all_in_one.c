/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_in_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:03:25 by fmick             #+#    #+#             */
/*   Updated: 2025/04/01 15:04:47 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	g_global = 0;

void	ft_handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_global++;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	signal(SIGINT, &ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

t_token	*find_last_token(t_token *token)
{
	t_token	*current;

	if (token == 0)
		return (0);
	current = token;
	while (current->next)
		current = current->next;
	return (current);
}

t_token	*add_node_token(t_token *token, char *str, t_type type)
{
	t_token	*new_node;
	t_token	*last;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (0);
	new_node->str = str;
	new_node->type = type;
	new_node->next = NULL;
	if (token == NULL)
	{
		new_node->index = 0;
		new_node->previous = NULL;
		return (new_node);
	}
	last = find_last_token(token);
	new_node->index = last->index + 1;
	new_node->previous = last;
	last->next = new_node;
	return (token);
}

t_token	*tokenize_input(t_mini *mini, char *input)
{
	int		i;
	char	*word;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (is_operator_char(input[i]))
			mini->token = if_operator(mini->token, input, &i);
		else
		{
			word = extract_word(&mini->extract, input, &i);
			if (word == NULL)
				return (line_cleanup(mini), NULL);
			mini->token = add_node_token(mini->token, word, COMMAND);
		}
	}
	if (mini->token == NULL)
		return (line_cleanup(mini), NULL);
	token_relativity(mini->token);
	expand_variables(mini);
	if (token_validity(mini) == false)
		return (line_cleanup(mini), NULL);
	return (mini->token);
}

void	arguments_before_pipe(t_token *token)
{
	t_token	*current;
	bool	flag_command;

	if (!token)
		return ;
	current = token;
	flag_command = false;
	while (current)
	{
		if (current->type == COMMAND)
		{
			if (flag_command == true)
				current->type = ARGUMENT;
			else
				flag_command = true;
		}
		else if (current->type == PIPE)
			flag_command = false;
		current = current->next;
	}
}

void	find_redirect(t_token *token)
{
	t_token	*current;

	current = token->next;
	while (current)
	{
		if (current->previous->type == RE_OUTPUT && current->type == COMMAND)
			current->type = OUTFILE;
		else if (current->previous->type == RE_APPEND
			&& current->type == COMMAND)
			current->type = APPEND_OUTFILE;
		else if (current->previous->type == RE_INPUT
			&& current->type == COMMAND)
			current->type = INFILE;
		else if (current->previous->type == HERE_DOC
			&& current->type == COMMAND)
			current->type = LIMITER;
		current = current->next;
	}
}

void	token_relativity(t_token *token)
{
	find_redirect(token);
	arguments_before_pipe(token);
}

t_re	*add_node_redirect(t_token *token)
{
	t_re	*new_node;

	new_node = malloc(sizeof(t_re));
	if (!new_node)
		return (0);
	new_node->str = ft_strdup(token->str);
	new_node->type = token->type;
	new_node->next = NULL;
	return (new_node);
}

t_re	*structurize_redirect(t_token *token)
{
	t_token	*current;
	t_re	*redirect;
	t_re	*first;

	first = NULL;
	current = token;
	while (current && current->type != PIPE)
	{
		if (first == NULL && (current->type == INFILE
				|| current->type == OUTFILE || current->type == APPEND_OUTFILE
				|| current->type == LIMITER))
		{
			first = add_node_redirect(current);
			redirect = first;
		}
		else if (current->type == INFILE || current->type == OUTFILE
			|| current->type == APPEND_OUTFILE || current->type == LIMITER)
		{
			redirect->next = add_node_redirect(current);
			redirect = redirect->next;
		}
		current = current->next;
	}
	return (first);
}

char	**make_command_into_array(t_token *token)
{
	t_token	*current;
	char	**array;
	size_t	counter;
	size_t	i;

	counter = calculate_number_of_commands(token);
	if (counter == 0)
		return (NULL);
	current = find_command(token);
	array = ft_calloc(counter + 1, sizeof(char *));
	if (current->str)
		array[0] = ft_strdup(current->str);
	current = current->next;
	i = 1;
	while (current && current->type != PIPE)
	{
		if (current->type == ARGUMENT)
			array[i++] = ft_strdup(current->str);
		current = current->next;
	}
	return (array);
}

t_line	*add_node_line(t_token *token)
{
	t_line	*new_node;

	new_node = malloc(sizeof(t_line));
	if (!new_node)
		return (NULL);
	new_node->command = make_command_into_array(token);
	new_node->redirect = structurize_redirect(token);
	new_node->next = NULL;
	return (new_node);
}

char	*if_empty_quote(char *before, char *sub, int len, char *org)
{
	char	*result;
	char	*temp;
	char	*temp1;

	temp = ft_substr(sub, len + 1, ft_strlen(org));
	temp1 = ft_strdup(before);
	result = ft_strjoin(temp1, temp);
	free_many(temp, before, org, temp1);
	return (result);
}

char	*handle_single_quote(char *org, char *sub, int *pos)
{
	char	*result;
	char	*temp;
	char	*temp1;
	int		len;

	len = 1;
	temp = ft_substr(org, 0, *pos);
	if (org[*pos + 1] == '\'')
		return (if_empty_quote(temp, sub, len, org));
	while (sub[len])
	{
		if (sub[len] == '\'')
			break ;
		len++;
	}
	temp1 = ft_substr(org, *pos + 1, len - 1);
	result = ft_strjoin(temp, temp1);
	free_many(temp, temp1, 0, 0);
	temp = ft_substr(sub, len + 1, ft_strlen(org));
	temp1 = ft_strjoin(result, temp);
	free_many(temp, result, org, 0);
	*pos += len - 1;
	return (temp1);
}

char	*check_double_quote_variable(t_mini *mini, char *org, int *pos)
{
	char	*temp2;
	int		len;

	len = 0;
	temp2 = org;
	(void)pos;
	while (temp2[len])
	{
		if (temp2[len] == '$')
			temp2 = handle_dollar_sign(mini, org, org + len, &len);
		else
			len++;
	}
	return (temp2);
}

char	*handle_double_quote(t_mini *mini, char *org, char *sub, int *pos)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		len;

	len = 1;
	temp1 = ft_substr(org, 0, *pos);
	if (sub[1] == '\"')
		return (if_empty_quote(temp1, sub, len, org));
	while (sub[len])
	{
		if (sub[len] == '\"')
			break ;
		len++;
	}
	temp2 = ft_substr(org, *pos + 1, len - 1);
	temp2 = check_double_quote_variable(mini, temp2, &len);
	temp3 = ft_strjoin(temp1, temp2);
	*pos += ft_strlen(temp2);
	free_many(temp1, temp2, 0, 0);
	temp1 = ft_substr(sub, len + 1, ft_strlen(org));
	temp2 = ft_strjoin(temp3, temp1);
	free_many(temp1, temp3, org, 0);
	return (temp2);
}

int	handle_dollar_get_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
			break ;
	}
	return (i);
}

char	*handle_dollar_sign_single(t_env *env, char *b4, char *org, int *pos)
{
	char	*result;
	char	*temp;
	char	*temp1;

	if (org[*pos + 1] == '$')
	{
		temp = ft_getenv(env, "SYSTEMD_EXEC_PID");
		temp1 = ft_strjoin(b4, temp);
		free(temp);
		temp = ft_substr(org, *pos + 2, ft_strlen(org));
		*pos += ft_strlen(temp1);
		result = ft_strjoin(temp1, temp);
		free(temp1);
		free(temp);
	}
	else
		result = ft_strjoin(b4, org + *pos + 1);
	free(org);
	free(b4);
	return (result);
}

char	*handle_exit_code(t_mini *mini, char *before, char *org, int *pos)
{
	char	*result;
	char	*temp;
	int		len;

	result = ft_itoa(mini->exit_flag);
	len = ft_strlen(result);
	temp = ft_strjoin(before, result);
	free(result);
	result = ft_strjoin(temp, org + *pos + 2);
	*pos += len;
	free(temp);
	return (result);
}

char	*handle_invalid_char(t_env *env, char *temp, char *org, int *pos)
{
	if (org[*pos + 1] == '\'' || org[*pos + 1] == '$' || org[*pos + 1] == '\"')
		return (handle_dollar_sign_single(env, temp, org, pos));
	return (free(temp), (void)(*(pos))++, org);
}

char	*handle_dollar_sign(t_mini *mini, char *org, char *sub, int *pos)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		len;

	mini->exit_flag = 58;
	temp1 = ft_substr(org, 0, *pos);
	if (sub[1] == '?')
		return (handle_exit_code(mini, temp1, org, pos));
	if (is_valid_char(sub[1], true) == false)
		return (handle_invalid_char(mini->env, temp1, org, pos));
	len = 1;
	while (is_valid_char(sub[len], false) == true)
		len++;
	temp3 = ft_substr(org, *pos + 1, len - 1);
	temp2 = ft_getenv(mini->env, temp3);
	free(temp3);
	temp3 = ft_strjoin(temp1, temp2);
	len += handle_dollar_get_end(temp1 + ft_strlen(temp1));
	*pos += ft_strlen(temp2);
	free_many(temp1, temp2, 0, 0);
	temp1 = ft_substr(sub, len, ft_strlen(org));
	temp2 = ft_strjoin(temp3, temp1);
	free_many(temp1, temp3, org, 0);
	return (temp2);
}

t_token	*find_pipe(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == PIPE)
		{
			ft_printf(G "find_functions: Found pipe at token: %s\n"RESET, token->str);
			return (current->next);
		}
		current = current->next;
	}
	return (NULL);
}

t_token	*find_command(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == COMMAND)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	init_extract(t_extract *extract, int pos)
{
	extract->start = pos;
	extract->len = 0;
	extract->in_quotes = false;
	extract->quote_char = '\0';
}

char	*check_unclosed_quote(t_extract *extract, int *pos, char *input)
{
	if (extract->in_quotes)
		return (ft_printf("Error: Unclosed quote detected\n"), NULL);
	*pos = extract->start + extract->len;
	return (ft_substr(input, extract->start, extract->len));
}

char	*extract_word(t_extract *extract, char *input, int *pos)
{
	init_extract(extract, *pos);
	while (input[extract->start + extract->len])
	{
		if ((input[extract->start + extract->len] == '\''
				|| input[extract->start + extract->len] == '\"')
			&& (!extract->in_quotes || input[extract->start
					+ extract->len] == extract->quote_char))
		{
			if (!extract->in_quotes)
			{
				extract->in_quotes = true;
				extract->quote_char = input[extract->start + extract->len];
			}
			else
			{
				extract->in_quotes = false;
				extract->quote_char = '\0';
			}
		}
		if (!extract->in_quotes && (input[extract->start + extract->len] == ' '
				|| is_operator_char(input[extract->start + extract->len])))
			break ;
		extract->len++;
	}
	return (check_unclosed_quote(extract, pos, input));
}

size_t	calculate_number_of_commands(t_token *token)
{
	t_token	*current;
	size_t	counter;

	current = token;
	counter = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == COMMAND || current->type == ARGUMENT)
			counter++;
		current = current->next;
	}
	return (counter);
}

size_t	count_pipes(t_token *token)
{
	t_token	*current;
	size_t	counter;

	current = token;
	counter = 0;
	while (current)
	{
		if (current->type == PIPE)
			counter++;
		current = current->next;
	}
	return (counter);
}


void	free_many(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	if (str4)
		free(str4);
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_redirect(t_re *redirect)
{
	t_re	*current;
	t_re	*next;

	current = redirect;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

void	line_cleanup(t_mini *mini)
{
	t_token	*token;
	t_token	*temp_token;
	t_line	*line;
	t_line	*temp_line;

	token = mini->token;
	while (token)
	{
		temp_token = token;
		token = token->next;
		free(temp_token->str);
		free(temp_token);
	}
	mini->token = NULL;
	line = mini->line;
	while (line)
	{
		temp_line = line;
		line = line->next;
		free_matrix(temp_line->command);
		free_redirect(temp_line->redirect);
		free(temp_line);
	}
	mini->line = NULL;
}

bool	is_valid_char(char c, bool first)
{
	if (first == true)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

bool	exit_validity(t_line *line)
{
	char	**temp_cmd;
	int		i;
	bool	char_flag;

	temp_cmd = line->command;
	char_flag = false;
	if (temp_cmd[1])
	{
		i = 0;
		while (temp_cmd[1][i])
		{
			if ((temp_cmd[1][0] == '+' || temp_cmd[1][0] == '-')
				&& char_flag == false)
				char_flag = true;
			else if (ft_isdigit(temp_cmd[1][i]) == 0)
				return (ft_printf("Error: Numeric argument required\n")
					, true);
			i++;
		}
		if (temp_cmd[2] != NULL)
			return (ft_printf("Error: Too many arguments\n"), false);
	}
	return (true);
}

//	loop through echo's arguments and check if each one is valid (aka -n).
//	the first one that is not valid,
//	the rest after that one should be printed (ex. "echo -n Hola -n")
//	should write "Hola -n")

bool	echo_validity(char *str)
{
	int		i;
	bool	first;

	i = 0;
	first = true;
	while (str[i])
	{
		if (first == true)
		{
			if (str[i] != '-')
				return (false);
			first = false;
		}
		else if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

// loop through export's arguments and check if each one is valid 
// (the ones that are not valid, aka return false,
// write an error message and continue to the next argument)

bool	export_validity(char *str)
{
	int		i;
	bool	first;
	char	*key;

	i = 0;
	first = true;
	key = strdup(str);
	while (str[i])
	{
		if (is_valid_char(key[i], first) == false)
		{
			ft_printf("NO GOOD\n");
			free(key);
			return (false);
		}
		if (first == true)
			first = false;
		i++;
	}
	free(key);
	return (true);
}
/*
bool	builtin_validity(t_line *line)
{
	if (!ft_strncmp(line->command[0], "exit", 5))
		return (exit_validity(line));
	return (true);
}*/

bool	token_validity(t_mini *mini)
{
	t_token	*current;

	current = mini->token;
	while (current)
	{
		if (current->next == NULL)
		{
			if (current->type == PIPE || current->type == RE_INPUT
				|| current->type == RE_OUTPUT || current->type == RE_APPEND
				|| current->type == HERE_DOC)
				return (ft_printf("Error: invalid syntax\n"), false);
		}
		else if ((current->type == PIPE && (current->next->type == PIPE
					|| current->index == 0)) || (current->type == RE_INPUT
				&& current->next->type != INFILE) || (current->type == RE_OUTPUT
				&& current->next->type != OUTFILE)
			|| (current->type == RE_APPEND
				&& current->next->type != APPEND_OUTFILE)
			|| (current->type == HERE_DOC && current->next->type != LIMITER))
			return (ft_printf("Error: invalid syntax\n"), false);
		current = current->next;
	}
	return (true);
}

int	is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_type	get_operator_type(char *op, int len)
{
	if (len == 1)
	{
		if (op[0] == '<')
			return (RE_INPUT);
		else if (op[0] == '>')
			return (RE_OUTPUT);
		else if (op[0] == '|')
			return (PIPE);
	}
	else if (len == 2)
	{
		if (op[0] == '<' && op[1] == '<')
			return (HERE_DOC);
		else if (op[0] == '>' && op[1] == '>')
			return (RE_APPEND);
	}
	return (COMMAND);
}

t_token	*if_operator(t_token *token, char *input, int *i)
{
	char	op[3];
	int		op_len;

	op_len = 1;
	op[0] = input[(*i)++];
	op[1] = 0;
	if (input[*i] == op[0] && (op[0] == '<' || op[0] == '>'))
	{
		op[1] = input[(*i)++];
		op_len = 2;
		op[2] = '\0';
	}
	token = add_node_token(token, ft_strdup(op), get_operator_type(op, op_len));
	return (token);
}
int	ft_update_value(t_env *env, char *key, char *value)
{
	t_env	*lst;
	t_env	*new_var;

	lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			free(lst->value);
			lst->value = ft_strdup(value);
			return (0);
		}
		lst = lst->next;
	}
	new_var = malloc(sizeof(t_env));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = NULL;
	lst->next = new_var;
	return (0);
}

static void	ft_go_to_dir(t_env *env, int av)
{
	char	*pwd;
	char	*oldpwd;
	char	*newpwd;
	int		i;

	pwd = ft_strdup(ft_find_key(env, "PWD"));
	oldpwd = ft_strdup(ft_find_key(env, "OLDPWD"));
	// cd ".."
	if (av == 0)
	{
		ft_update_value(env, "OLDPWD", pwd);
		i = ft_strlen(pwd);
		while (i > 0 && pwd[i] != '/')
			i--;
		if (i > 0)
			pwd[i] = '\0';
		newpwd = ft_strdup(pwd);
		ft_update_value(env, "PWD", newpwd);
		free(newpwd);
	}
	// cd "-"
	else if (av == 1)
	{
		ft_update_value(env, "OLDPWD", pwd);
		newpwd = ft_strdup(oldpwd);
		ft_update_value(env, "PWD", newpwd);
		free(newpwd);
	}
	free(pwd);
	free(oldpwd);
}

void	ft_cd(char **av, t_env *env)
{
	char	*home;

	home = ft_find_key(env, "HOME");
	if (av[1] == NULL || ft_strncmp(av[1], "~", 2) == 0)
	{
		if (home)
			ft_update_value(env, "PWD", home);
	}
	else if (ft_strncmp(av[1], "..", 3) == 0)
		ft_go_to_dir(env, 0);
	else if (ft_strncmp(av[1], "-", 2) == 0)
		ft_go_to_dir(env, 1);
	else if (av[1][0] == '/')
	 {
		if (access(av[1], F_OK) == 0)
			ft_update_value(env, "PWD", av[1]);
	 }
	else
		ft_update_value(env, "PWD", av[1]);
}

static int	ft_nbr_of_args(char **args)
{
	int	i;

	i = 0;
	while(args[i])
		i++;
	return (i);
}
// ft_echo(["echo", "hello", "world"]);
// Expected output: "hello world"
// handles option -n to print the arguments
// without a \n at the end
int	ft_echo(char **args)
{
	int	nflag;
	int i;

	nflag = 0;
	i = 1;
	if (ft_nbr_of_args(args) > 1)
	{
		while (args[i] && echo_validity(args[i]) == true)
		{
			nflag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1])
			{
				write(1, " ", 1);
			}
			i++;
		}
	}
	if (nflag == 0)
		write (1, "\n", 1);
	return (0);
}
int	ft_env(t_env *env)
{
	t_env	*lst;

	lst = env;
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->value)
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (0);
}
static int ft_strisnum(const char *str)
{
    int i = 0;

    if (!str || !*str) 
        return (0);
    if (str[i] == '-' || str[i] == '+')
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void    ft_exit(t_mini *mini, char **cmd)
{
    int exit_status;
	bool eflag;

	eflag = true;
	ft_printf("exit\n");
    if (cmd[1] && ft_strisnum(cmd[1]) && exit_validity(mini->line) == false)
    {
        mini->exit_status = 255;
		eflag = false;
    }
    else if (cmd[1])
        mini->exit_status = ft_atoi(cmd[1]);
    else
	{
        mini->exit_status = 0;
	}
	if (eflag == true)
	{
    	exit_status = mini->exit_status;
		line_cleanup(mini);
    	free_env(mini->env);
    	free(mini);
    	exit(exit_status);
	}
}

int	ft_pwd(t_env *env)
{
	char	*cwd;
	cwd = ft_find_key(env, "PWD"); // NULL allows getcwd to allocate the buffer
	if (cwd)
	{
		printf("%s\n", cwd);
		return (0); // success
	}
	else
	{
		char buffer[4096];
        if (getcwd(buffer, sizeof(buffer)) != NULL)
        {
            printf("%s\n", buffer);
            return (0); // success
        }
        else
        {
            perror("pwd");
            return (-1); // failure
        }
	}
}

int	ft_unset(t_mini *mini, char **av)
{
    int	i;

    i = 1;
    if (!av[i])
        return (0);
    while (av[i])
    {
        if (!export_validity(av[i]))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(av[i], STDERR_FILENO);
            ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
        }
        else
            ft_unset_key(mini->env, av[i]);
        i++;
    }
    return (0);
}

char    *ft_getenv(t_env *env, char *key)
{
    t_env   *current;

    current = env;
    while (current)
    {
        if (ft_strncmp(key, current->key, ft_strlen(key) + 1) == 0)
            return (ft_strdup(current->value));
        current = current->next;
    }
    return (ft_strdup(""));
}

char    *ft_find_key(t_env *env, char *key)
{
    t_env   *lst;

    lst = env;
    while (lst)
    {
        if (ft_strcmp(lst->key, key) == 0)
            return (lst->value);
        lst = lst->next;
    }
    return (NULL);
}

char    *ft_update_key(t_env *env, char *key, char *new_value)
{
    t_env   *lst;

    lst = env;
    while (lst)
    {
        if (ft_strcmp(lst->key, key) == 0)
        {
            free(lst->value);
            lst->value = ft_strdup(new_value);
            return NULL;
        }
        lst = lst->next;
    }
    return (NULL);
}

void    ft_unset_key(t_env *env, char *key)
{
    t_env *lst;
    t_env *prev;

    lst = env;
    prev = NULL;

    // Search for the node with the matching key
    while (lst)
    {
        if (ft_strcmp(lst->key, key) == 0)
        {
            if (prev == NULL)
                env = lst->next;
            else
                prev->next = lst->next;
            free(lst->key);
            free(lst->value);
            free(lst);
            return;
        }
        prev = lst;
        lst = lst->next;
    }
    // error if key not found
}

char **ft_env_to_array(t_env *env)
{
    char **env_array;
	char *temp;
    t_env *cur;
    int count;
    int i;

    count = 0;
    cur = env;
    while (cur)
    {
        count++;
        cur = cur->next;
    } // count
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
    {
        perror("malloc");
        return (NULL);
    }
    i = 0;
    cur = env;
    while (cur)
    {
        if (cur->key && cur->value)
        {
            env_array[i] = ft_strjoin(cur->key, "=");
			temp = env_array[i];
			env_array[i] = ft_strjoin(temp, cur->value);
			free (temp);
            if (!env_array[i])
            {
                perror("malloc u dimwit");
                // Free
                while (i > 0)
                    free(env_array[--i]);
                free(env_array);
                return (NULL);
            }
            i++;
        }
        cur = cur->next;
    }
    env_array[i] = NULL;
    return (env_array);
}

void	ft_env_display(t_env *env)
{
	t_env	*lst;
	char	*tmp;
	char	*joined;
	
	lst = env;
	while (lst)
	{
		if (lst->key && lst->value)
		{
			tmp = ft_strjoin(lst->key, "=");
			joined = ft_strjoin(tmp, lst->value);
			free(tmp);
			free(joined);
		}
		lst = lst->next;
	}
	lst->next = NULL;
}

t_env	*ft_add_env_node(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (value != NULL)
		env->value = ft_strdup(value);
	else
		env->value = ft_strdup("");
	env->next = NULL;
	if (!env->key || !env->value)
	{
		free(env->key);
		free(env->value);
		free(env);
		return NULL;
	}
	return (env);
}

t_env	*ft_init_env(char **envp)
{
	char	**tmp;
	t_env	*env;
	int		i;
	t_env	*last;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		if (!tmp)
			return (NULL);
		if (env == NULL)
			env = ft_add_env_node(tmp[0], tmp[1]);
		else
		{
			last = env;
			while (last->next)
				last = last->next;
			last->next = ft_add_env_node(tmp[0], tmp[1]);
		}
		i++;
		free_matrix(tmp);
	}
	return (env);
}

char	*check_absolute_command(char *command)
{
	if (access(command, X_OK) == 0)
		return (command);
	else
		return (NULL);
}

char	*check_external(t_env *env, char *command)
{
	char	**all_paths;
	char	*temp;
	char	*str;
	char	*str1;
	int		i;
	
	if (ft_strncmp(command, "/", 1) == 0)
		return (check_absolute_command(command));
	temp = ft_getenv(env, "PATH");
	if (ft_strncmp(temp, "PATH=", 5) == 0)
		temp += 5;
	all_paths = ft_split(temp + 5, ':');
	free(temp);
	i = 0;
	while (all_paths[i])
	{
		str = ft_strjoin(all_paths[i], "/");
		str1 = ft_strjoin(str, command);
		free(str);
		if (access(str1, X_OK) == 0)
		{
			free_matrix(all_paths);
		//	free(command);
			return (str1);
		//	return(free_matrix(all_paths), free(command), str1);
		}
		free(str1);
		i++;
	}
	free_matrix(all_paths);
	return (NULL);
}

void	ft_handle_external(t_mini *mini, char **args)
{
	pid_t	cpid;
	char 	*temp;
	
	temp = check_external(mini->env, args[0]);
	cpid = fork();
    if (cpid < 0)
    {
        perror("fork");
        free(temp);
        exit(1);
    }
	if (cpid == 0)
	{
		ft_handle_redirections(mini);
		if (execve(temp, args, mini->env_array) == -1)
		{
			free(temp);
			exit(EXIT_FAILURE);
		}
	}
	else // parent
	{
        waitpid(cpid, NULL, 0);
	}
	free(temp);
}
