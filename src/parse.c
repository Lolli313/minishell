/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:31 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/04 16:30:30 by aakerblo         ###   ########.fr       */
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

char	*handle_command(char *command)
{
//	t_token	token;

//	initialize(&token);
	if (check_builtin(command) == true || check_external(command) == true)
	{
		ft_printf("SUCCESS");
		/*token.str = command;
		token.type = COMMAND;
		token.index = 0;
		token.previous = NULL;*/
	//	token = tokenizer(command, COMMAND, &token);
	}
	else
		ft_printf("THIS IS NOT A VALID COMMAND YOU KNOBHEAD");
	return (NULL);
}

void	parse_string(char *line)
{
	char	**strings;

	strings = ft_split(line, ' ');
	handle_command(strings[0]);
}
