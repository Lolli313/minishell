/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:31 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/16 16:55:54 by aakerblo         ###   ########.fr       */
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
/*
char	*extract_env_variable(char *str)
{
	
}




char	*ft_getenv(t_env *env, char *str)
{
	t_env	*current;
	
	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, str, ft_strlen(str)) == 0)
		return (current->value);
		current = current->next;
	}
	while (*str)
	{

	}
	return (str);
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

int is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_type get_operator_type(char *op, int len)
{
    if (len == 1) {
        if (op[0] == '<')
            return RE_INPUT;
        else if (op[0] == '>')
            return RE_OUTPUT;
        else if (op[0] == '|')
            return PIPE;
    } else if (len == 2) {
        if (op[0] == '<' && op[1] == '<')
            return HERE_DOC;
        else if (op[0] == '>' && op[1] == '>')
            return RE_APPEND;
    }
    return COMMAND;
}

void	init_extract(t_extract *extract, int pos)
{
	extract->start = pos;
	extract->len = 0;
	extract->in_quotes = false;
	extract->quote_char = '\0';
}

char	*check_unclosed_quote(char *input, int start, int len, bool in_quotes)
{
	if (in_quotes)
		return (ft_printf("Error: Unclosed quote detected\n"), NULL);
	return (ft_substr(input, start, len));
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
	if (input[*i] == op[0] && (op[0] == '<' || op[0] == '>'))
	{
		op[1] = input[(*i)++];
		op_len = 2;
	}
	token = add_node_token(token, ft_strdup(op), get_operator_type(op, op_len));
	return (token);
}

t_token *tokenize_input(t_mini *mini, t_token *token, char *input)
{
    int		i;
	char	*word;

    i = 0;
    while (input[i]) 
	{
        if (input[i] == ' ' || input[i] == '\t') 
			i++;
        else if (is_operator_char(input[i])) 
			token = if_operator(token, input, &i);
        else
		{
			word = extract_word(&mini->extract, input, &i);
			if (word == NULL)
				return (NULL);
			token = add_node_token(token, word, COMMAND);
		}
    }
	token_relativity(token);
    return (token);
}

void	parse_string(t_mini *mini, char *line)
{
	if (ft_strncmp(line, "\0", 1) == 0)
		return ;
	mini->token = NULL;
	mini->line = NULL;
	mini->token = tokenize_input(mini, mini->token, line);
	if (mini->token == NULL)
		return ;
	print_tokens(mini->token);
//	mini->line = structurize_line(mini->token, mini->line);
//	print_lines(mini->line);
//	free_matrix(strings);
//	free_token_list(token);
}
