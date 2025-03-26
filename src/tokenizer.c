/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:57 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/26 11:10:31 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	t_token *new_node;
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
		else if (current->previous->type == RE_APPEND && current->type == COMMAND)
			current->type = APPEND_OUTFILE;
		else if (current->previous->type == RE_INPUT && current->type == COMMAND)
			current->type = INFILE;
		else if (current->previous->type == HERE_DOC && current->type == COMMAND)
			current->type = LIMITER;
		current = current->next;
	}
}

t_token	*find_command(t_token *token)
{
	t_token *current;

	current = token;
	while (current)
	{
		if (current->type == COMMAND)
			return (current);
		current = current->next;
	}
	return (NULL);
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

char	*find_last_type(t_token *token, t_type type)
{
	t_token	*current;
	char	*last_file;

	last_file = NULL;
	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == type)
			last_file = current->str;
		current = current->next;
	}
	return (last_file);
}

t_token	*find_pipe(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == PIPE)
			return (current->next);
		current = current->next;
	}
	return (NULL);
}

size_t	calculate_number_of_types(t_token *token, t_type type)
{
	t_token	*current;
	size_t	counter;

	current = token;
	counter = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == type)
			counter++;
		current = current->next;
	}
	return (counter);
}

char	**make_type_into_array(t_token *token, t_type type)
{
	t_token	*current;
	char	**array;
	size_t	counter;
	size_t	i;

	counter = calculate_number_of_types(token, type);
	if (counter == 0)
		return (NULL);
	array = ft_calloc(counter + 1, sizeof(char *));
	current = token->next;
	i = 0;
	while (current && current->type != PIPE)
	{
		if (current->previous->type == type)
			array[i++] = current->str;
		current = current->next;
	}
	return (array);
}

int	infile_or_delimiter(t_token *token)
{
	t_token	*current;
	int		flag;

	current = token;
	flag = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == RE_INPUT)
			flag = 1;
		else if (current->type == HERE_DOC)
			flag = 2;
		current = current->next;
	}
	return (flag);
}

int	outfile_or_append(t_token *token)
{
	t_token	*current;
	int		flag;

	current = token;
	flag = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == RE_OUTPUT)
			flag = 1;
		else if (current->type == RE_APPEND)
			flag = 2;
		current = current->next;
	}
	return (flag);
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
	t_token		*current;
	t_re	*redirect;
	t_re	*first;

	first = NULL;
	current	= token;
	while (current && current->type != PIPE)
	{
		if (first == NULL && (current->type == INFILE || current->type == OUTFILE || current->type == APPEND_OUTFILE || current->type == LIMITER))
		{
			first = add_node_redirect(current);
			redirect = first;
		}
		else if (current->type == INFILE || current->type == OUTFILE || current->type == APPEND_OUTFILE || current->type == LIMITER)
		{
			redirect->next = add_node_redirect(current);
			redirect = redirect->next;
		}
		current = current->next;
	}
	return (first);
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

bool	exit_validity(t_line *line)
{
	t_line	*temp_line;
	char	**temp_cmd;
	int		i;
	bool	char_flag;

	temp_line = line->next;
	temp_cmd = line->command;
	char_flag = false;
	if (temp_cmd[1])
	{
		i = 0;
		while (temp_cmd[1][i])
		{
			if ((temp_cmd[1][0] == '+' || temp_cmd[1][0] == '-') && char_flag == false)
				char_flag = true;
			else if (ft_isdigit(temp_cmd[1][i]) == 0)
				return (ft_printf("Error: Numeric argument required\n"), true);
			i++;
		}
		if (temp_cmd[2] != NULL)
			return (ft_printf("Error: Too many arguments\n"), false);
	}
	return (true);
}

// loop through echo's arguments and check if each one is valid (aka -n), the first one that is not valid,
// the rest after that one should be printed (ex. "echo -n Hola -n" should write "Hola -n")

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
				return (ft_printf("NONONO\n"), false);
			first = false;
		}
		else if (str[i] != 'n')
			return (ft_printf("NONONO\n"), false);
		i++;
	}
	ft_printf("YIPPEEEE\n");
	return (true);
}

// loop through export's arguments and check if each one is valid (the ones that are not valid, aka return false,
// write an error message and continue to the next argument)

bool	export_validity(char *str)
{
	int		i;
	bool	first;
	char	**key;

	i = 0;
	first = true;
	key = ft_split(str, '=');
	while (key[0][i])
	{
		if (is_valid_char(key[0][i], first) == false)
		{
			ft_printf("NO GOOD\n");
			free_matrix(key);
			return (false);
		}
		if (first == true)
			first = false;
		i++;
	}
	free_matrix(key);
	return (true);
}

bool	builtin_validity(t_line *line)
{
	if (!ft_strncmp(line->command[0], "exit", 5))
		return (exit_validity(line));
	else if (!ft_strncmp(line->command[0], "export", 7))
		return (export_validity(line->command[1]));
//	else if (!ft_strncmp(line->command[0], "echo", 5))
//		return (echo_validity(line->command[1]));
	return (true);
}

t_line	*structurize_line(t_mini *mini)
{
	t_line	*current;
	t_token	*next_pipe;
	size_t	pipes;
	size_t	i;

	pipes = count_pipes(mini->token);
	mini->nbr_of_pipes = pipes;
	i = 0;
	mini->line = add_node_line(mini->token);
	current = mini->line;
	next_pipe = mini->token;
	while (i < pipes)
	{
		next_pipe = find_pipe(next_pipe);
		current->next = add_node_line(next_pipe);
		current = current->next;
		i++;
	}
	if (builtin_validity(mini->line) == false)
		return (line_cleanup(mini), NULL);
	return (mini->line);
}

void	token_relativity(t_token *token)
{
	find_redirect(token);
	arguments_before_pipe(token);
}

t_token	*tokenizer(char *str, t_type type, t_token *token)
{
	token = add_node_token(token, str, type);
	return (token);
}
