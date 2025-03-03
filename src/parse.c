/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:31 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/03 14:44:34 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_command(char *command)
{
	if (ft_strncmp(command, "echo", 5))
		return (1);
	else if (ft_strncmp(command, "cd", 3))
		return (1);
	else if (ft_strncmp(command, "pwd", 4))
		return (1);
	else if (ft_strncmp(command, "export", 7))
		return (1);
	else if (ft_strncmp(command, "unset", 6))
		return (1);
	else if (ft_strncmp(command, "env", 4))
		return (1);
	else if (ft_strncmp(command, "exit", 5))
		return (1);
	else
		return (0);
}

char	*handle_command(char *command)
{
	t_token	token;

	initialize(&token);
	if (check_command(command) == true)
	{
		/*token.str = command;
		token.type = COMMAND;
		token.index = 0;
		token.previous = NULL;*/
		token = tokenizer(command, COMMAND, &token);
	}
}

void	parse_string(char *line)
{
	char	**strings;

	strings = ft_split(line, ' ');
	handle_command(strings[0]);
}
