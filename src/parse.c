/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:31 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/19 11:54:07 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_builtin(char *command)
{
	if (!ft_strncmp(command, "echo", 5))
		return (true);
	else if (!ft_strncmp(command, "cd", 3))
		return (true);
	else if (!ft_strncmp(command, "pwd", 4))
		return (true);
	else if (!ft_strncmp(command, "export", 7))
		return (true);
	else if (!ft_strncmp(command, "unset", 6))
		return (true);
	else if (!ft_strncmp(command, "env", 4))
		return (true);
	else if (!ft_strncmp(command, "exit", 5))
		return (true);
	else if (!ft_strncmp(command, "$?", 3))
		return (true);
	else
		return (false);
}

bool	check_external(char *command)
{
	char	**all_paths;
	char	*temp;
	char	*str;
	char	*str1;

	temp = getenv("PATH");
	all_paths = ft_split(temp + 5, ':');
	while (*all_paths)
	{
		str = ft_strjoin(*all_paths, "/");
		str1 = ft_strjoin(str, command);
		free(str);
		if (access(str1, X_OK) == 0)
			return (free(str1), true);
		free(str1);
		all_paths++;
	}
	return (false);
}

bool	handle_command(char *command)
{
	if (check_builtin(command) == true || check_external(command) == true)
		return (ft_printf("SUCCESS\n"), true);
	else
		return (ft_printf("THIS IS NOT A VALID COMMAND YOU KNOBHEAD\n"), false);
}

void	free_token_list(t_token *token)
{
	t_token	*current;
	t_token	*next;

	current = token;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	print_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		ft_printf("%s is of type %d on the index %d\n", current->str, current->type, current->index);
		current = current->next;
	}
}
/*
int	token_type(char *strings)
{
	if (!ft_strncmp(strings, "<", 2))
		return (RE_INPUT);
	else if (!ft_strncmp(strings, ">", 2))
		return (RE_OUTPUT);
	else if (!ft_strncmp(strings, ">>", 3))
		return (RE_APPEND);
	else if (!ft_strncmp(strings, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(strings, "<<", 3))
		return (HERE_DOC);
	else
		return (COMMAND);
}

char	*extract_env_variable(char *str)
{
	
}






char	*expand_variable(char *token, t_mini *mini)
{
	char	*value;
	char	*variable;
	
	variable = token + 1;
	if (ft_strncmp(token, "$?", 3))
		return (mini->exit_flag);
	value = ft_getenv(mini->env, token + 1);
	if (value == NULL)
		ft_printf("ERROR\n");
	return (value);
}

bool	check_dollar_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
			return (true);
	}
	return (false);
}*/

//    \' \" \\ \$ can be escaped with a backslash in bash without -e flag"
//    make a check for unclosed quotes
/*
size_t	find_specific_character(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*handle_single_quote(char *str)
{
	char	*new_str;
	int		len;

	len = find_specific_character(str, '\'');
	new_str = ft_substr(str, 0, len);
	return (new_str);
}

char	*check_expand_variable(char	*str)
{
	char	*new_str;
	char	*temp;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			handle_single_quote(str + i + 1);
		else if (str[i] == '\"')
			handle_double_quote(str + i + 1);			
	}
}

t_token	*handle_input(t_mini *mini, t_token *token, char **strings)
{
	t_token	*current;
	size_t	i;

	i = 0;
	while (strings[i])
	{
		token = tokenizer(strings[i], token_type(strings[i]), token);
		i++;
	}
	//	if (token->type == 0 && handle_command(strings[0]) == false)
	//		return (NULL);
	token_relativity(token);
	current = token;
	while (current)
	{
		if (current->str)
			current->str = check_expand_variable(current->str);
		current = current->next;
	}
	return (token);
}

void	print_lines(t_line *line)
{
	t_line	*current;
	int		i;
	
	current = line;
	while (current)
	{
		i = 0;
		ft_printf("COMMAND: ");
		while (current->command && current->command[i])
			ft_printf("%s ", current->command[i++]);
		
		i = 0;
		ft_printf("INFILE: ");
		while (current->infile && current->infile[i])
			ft_printf("%s ", current->infile[i++]);
		
		i = 0;
		ft_printf("DELIMITER: ");
		while (current->delimiter && current->delimiter[i])
			ft_printf("%s ", current->delimiter[i++]);
		
		ft_printf("INFILE OR DELIMITER: %d ", current->infile_or_delimiter);

		i = 0;
		ft_printf("OUTFILE: ");
		while (current->outfile && current->outfile[i])
			ft_printf("%s ", current->outfile[i++]);
		
		i = 0;
		ft_printf("APPEND: ");
		while (current->append && current->append[i])
			ft_printf("%s ", current->append[i++]);

		ft_printf("OUTFILE OR APPEND: %d ", current->outfile_or_append);		
		
		ft_printf("\n");
		current = current->next;
	}
}*/

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

char	*if_empty_single_quote(char *before, char *sub, int len, char *org)
{
	char	*result;

	result = ft_strjoin(ft_strdup(before), ft_substr(sub, len + 1, ft_strlen(org)));
	free(before);
	free(org);
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
		return (if_empty_single_quote(temp, sub, len, org));
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

bool	is_valid_char(char c, bool first)
{
	if (first == true)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
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

char	*handle_dollar_sign_single(char *before, char *sub, char *org)
{
	char	*result;

	result = ft_strjoin(before, sub + 1);
	free(org);
	free(before);
	return (result);
}

char	*handle_dollar_sign(t_env *env, char *org, char *sub, int *pos)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		len;

//	if (org[1] == 0)
//		return ((void)(*(pos))++, org);
	len = 1;
//	if (sub[len] == '\'')
//		handle_single_quote()
	temp1 = ft_substr(org, 0, *pos);
	if (org[1] == 0 || is_valid_char(sub[len], true) == false)
	{
		if (sub[len] == '\'')
			return (handle_dollar_sign_single(temp1, sub, org));
		return ((void)(*(pos))++, org);
	}
	//else
	{
		while (is_valid_char(sub[len], false) == true)
			len++;
		temp3 = ft_substr(org, *pos + 1, len - 1);
		temp2 = ft_getenv(env, temp3);
		free(temp3);
		temp3 = ft_strjoin(temp1, temp2);
		len += handle_dollar_get_end(temp1 + ft_strlen(temp1));
	}
	*pos += ft_strlen(temp2);
	free_many(temp1, temp2, 0, 0);
	temp1 = ft_substr(sub, len, ft_strlen(org));
	temp2 = ft_strjoin(temp3, temp1);
	free_many(temp1, temp3, org, 0);
	return (temp2);
}

void	expand_variables(t_mini *mini)
{
	t_token	*current;
	int	i;

	current = mini->token;
	while (current)
	{
		i = 0;
		while (current->str[i])
		{
			if (current->str[i] == '\'')
				current->str = handle_single_quote(current->str, current->str + i, &i);
			/*else if (current->str[i] == '\"')
				current->str = handle_double_quote(current->str, current->str + 1, &i);*/
			else if (current->str[i] == '$')
				current->str = handle_dollar_sign(mini->env, current->str, current->str + i, &i);
			else
				i++;
		}
		current = current->next;
	}
}

int is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_type get_operator_type(char *op, int len)
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

void	init_extract(t_extract *extract, int pos)
{
	extract->start = pos;
	extract->len = 0;
	extract->in_quotes = false;
	extract->quote_char = '\0';
}
/*
char	*check_unclosed_quote(char *input, int start, int len, bool in_quotes)
{
	if (in_quotes)
		return (ft_printf("Error: Unclosed quote detected\n"), NULL);
	return (ft_substr(input, start, len));
}*/

char *extract_word(t_extract *extract, char *input, int *pos)
{
	init_extract(extract, *pos);
    while (input[extract->start + extract->len])
	{
        if ((input[extract->start + extract->len] == '\'' || input[extract->start + extract->len] == '\"') && 
            (!extract->in_quotes || input[extract->start + extract->len] == extract->quote_char)) 
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
        if (!extract->in_quotes && (input[extract->start + extract->len] == ' ' || is_operator_char(input[extract->start + extract->len])))
			break; 
        extract->len++;
    }
	if (extract->in_quotes)
		return (ft_printf("Error: Unclosed quote detected\n"), NULL);
	*pos = extract->start + extract->len;
    return (ft_substr(input, extract->start, extract->len));
}

t_token	*if_operator(t_token *token, char *input, int *i)
{
	char	op[2];
	int		op_len;

	op_len = 1;
	op[0] = input[(*i)++];
	op[1]= 0;
	if (input[*i] == op[0] && (op[0] == '<' || op[0] == '>'))
	{
		op[1] = input[(*i)++];
		op_len = 2;
	}
	token = add_node_token(token, ft_strdup(op), get_operator_type(op, op_len));
	return (token);
}

t_token *tokenize_input(t_mini *mini, char *input)
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
				return (NULL);
			mini->token = add_node_token(mini->token, word, COMMAND);
		}
    }
	token_relativity(mini->token);
	expand_variables(mini);
    return (mini->token);
}

void	parse_string(t_mini *mini, char *line)
{
	if (ft_strncmp(line, "\0", 1) == 0)
		return ;
	mini->token = NULL;
	mini->line = NULL;
	mini->token = tokenize_input(mini, line);
	if (mini->token == NULL)
		return ;
	print_tokens(mini->token);
//	mini->line = structurize_line(mini->token, mini->line);
//	print_lines(mini->line);
//	free_matrix(strings);
//	free_token_list(token);
}
