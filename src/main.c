/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/22 16:11:54 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// unsure how to deal with 'ABC=hola' as input
// do we add that to the env variables or no

// TODO signals (CTRL + D and CTRL + \), talk with Francois about how to handle the $?
// look into echo -n and how the syntax should be handled

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;

	(void)ac;
	(void)av;
	char	*line;
	mini = malloc(sizeof(t_mini));
	mini->env = init_env(envp);
	while (1)
	{
		line = readline(G "😭 minishell$ " RESET);
		if (!line)
		{
			ft_printf("exit");
			break ;
		}
		parse_string(mini, line);
		line_cleanup(mini);
		free(line);
	}
	free_env(mini->env);
	free(mini);
	return (1);
}
