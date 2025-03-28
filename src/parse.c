/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:31 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/28 11:38:39 by aakerblo         ###   ########.fr       */
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
	all_paths = ft_split(temp + 5, ':');
	free(temp);
	i = 0;
	while (all_paths[i])
	{
		str = ft_strjoin(all_paths[i], "/");
		str1 = ft_strjoin(str, command);
		free(str);
		if (access(str1, X_OK) == 0)
			return (free_matrix(all_paths), free(command), str1);
		free(str1);
		i++;
	}
	free_matrix(all_paths);
	return (NULL);
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
		ft_printf("%s is of type %d on the index %d\n", current->str,
			current->type, current->index);
		current = current->next;
	}
}

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

void	expand_variables(t_mini *mini)
{
	t_token	*current;
	int		i;

	current = mini->token;
	while (current)
	{
		i = 0;
		while (current->str[i])
		{
			if (current->str[i] == '\'')
				current->str = handle_single_quote(current->str, current->str
						+ i, &i);
			else if (current->str[i] == '\"')
				current->str = handle_double_quote(mini, current->str,
						current->str + i, &i);
			else if (current->str[i] == '$')
				current->str = handle_dollar_sign(mini, current->str,
						current->str + i, &i);
			else
				i++;
		}
		current = current->next;
	}
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

t_token	*if_operator(t_token *token, char *input, int *i)
{
	char	op[2];
	int		op_len;

	op_len = 1;
	op[0] = input[(*i)++];
	op[1] = 0;
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
	if (mini->line == NULL)
		return ;
	print_lines(mini->line);
}
