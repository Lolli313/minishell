/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:49:29 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/01 13:59:49 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
