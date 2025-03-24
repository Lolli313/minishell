/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/24 14:58:11 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// unsure how to deal with 'ABC=hola' as input
// do we add that to the env variables or no

// TODO signals (CTRL + D and CTRL + \), talk with Francois about how to handle the $?
// look into echo -n and how the syntax should be handled

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;
	char	**cmd_args;

	(void)ac;
	(void)av;
	char	*input;
	mini = malloc(sizeof(t_mini));
	mini->env = ft_init_env(envp);
	while (1)
	{
		input = readline(G "😭 minishell$ " RESET);
		ft_printf(B "Received input: %s\n" RESET, input);
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		parse_string(mini, input);
		if (*input)
		{
			add_history(input);
		}
		cmd_args = ft_split(input, ' ');
		if (cmd_args && cmd_args[0])
		{
			if (strcmp(input, "exit") == 0)
			{
				mini->exit_flag = 0;
				free_matrix(cmd_args);
				free(input);
				break;
			}
			ft_handle_pipes(mini, envp);
			ft_handle_builtin(cmd_args, mini);
		}
		line_cleanup(mini);
		free(input);
	}
	free_env(mini->env);
	free(mini);
	return (1);
}
