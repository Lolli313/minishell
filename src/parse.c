/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:31 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/24 16:44:17 by aakerblo         ###   ########.fr       */
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
	else
		return (false);
}

bool	check_external(t_env *env, char *command)
{
	char	**all_paths;
	char	*temp;
	char	*str;
	char	*str1;
	int		i;

	if (ft_strncmp(command, "/", 1) == 0)
	{
		if (access(command, X_OK) == 0)
			return (true);
		else
			return (false);
	}
	temp = ft_getenv(env, "PATH");
	all_paths = ft_split(temp + 5, ':');
	free(temp);
	i = 0;
	while (all_paths[i])
	{
		str = ft_strjoin(all_paths[i], "/");
		str1 = ft_strjoin(str, command);
		free(str);
		if (access(str1, X_OK) == 0)
			return (free_matrix(all_paths), free(str1), true);
		free(str1);
		i++;
	}
	free_matrix(all_paths);
	return (false);
}

bool	handle_command(t_env *env, char *command)
{
	if (ft_strlen(command) && (check_builtin(command) == true || check_external(env, command)) == true)
		return (ft_printf("%s is a valid command :)\n", command), true);
	else
		return (ft_printf("%s IS NOT A VALID COMMAND YOU KNOBHEAD\n", command), false);
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
}*/



void	print_lines(t_line *line)
{
	t_line	*current;
	t_re	*temp_re;
	int		i;
	
	current = line;
	while (current)
	{
		i = 0;
		ft_printf("COMMAND: ");
		while (current->command && current->command[i])
			ft_printf("%s ", current->command[i++]);
		
		i = 0;
		ft_printf("\nREDIRECTS: ");
		temp_re = current->redirect;	
		while (temp_re)
		{
			ft_printf("%s ", temp_re->str);
			ft_printf("is type %d, ", temp_re->type);
			ft_printf("\n");
			temp_re = temp_re->next;
		}
		ft_printf("\n");
		current = current->next;
	}
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

char	*handle_dollar_sign_single(t_mini *mini, char *before, char *org, int *pos)
{
	char	*result;
	char	*temp;

	if (org[*pos + 1] == '$')
	{
		(void)(*(pos))++;
		result = ft_strjoin(before, org + *pos);
	}
	else
		result = ft_strjoin(before, org + *pos + 1);
	free(org);
	free(before);
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
	{
		if (sub[1] == '\'' || sub[1] == '$' || sub[1] == '\"')
			return (handle_dollar_sign_single(mini, temp1, org, pos));
		return (free(temp1), (void)(*(pos))++, org);
	}
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
//	if (temp2 != org)
//		free(org);
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
			else if (current->str[i] == '\"')
				current->str = handle_double_quote(mini, current->str, current->str + i, &i);
			else if (current->str[i] == '$')
				current->str = handle_dollar_sign(mini, current->str, current->str + i, &i);
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

bool	token_validity(t_mini *mini)
{
	t_token	*current;

	current = mini->token;
	while (current)
	{
		if (current->type == COMMAND && handle_command(mini->env, current->str) == false)
			return (false);
		else if (current->next == NULL)
		{
			if (current->type == PIPE || current->type == RE_INPUT || current->type == RE_OUTPUT || current->type == RE_APPEND || current->type == HERE_DOC)
				return (ft_printf("Error: invalid syntax\n"), false);
		}
		else if (current->type == PIPE && (current->next->type == PIPE || current->index == 0))
			return (ft_printf("Error: invalid syntax\n"), false);
		else if (current->type == RE_INPUT && current->next->type != INFILE)
			return (ft_printf("Error: invalid syntax\n"), false);
		else if (current->type == RE_OUTPUT && current->next->type != OUTFILE)
			return (ft_printf("Error: invalid syntax\n"), false);
		else if (current->type == RE_APPEND && current->next->type != APPEND_OUTFILE)
			return (ft_printf("Error: invalid syntax\n"), false);
		else if (current->type == HERE_DOC && current->next->type != LIMITER)
			return (ft_printf("Error: invalid syntax\n"), false);
		current = current->next;
	}
	return (true);
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
	mini->line = structurize_line(mini);
	print_lines(mini->line);
//	free_matrix(strings);
//	free_token_list(token);
}
