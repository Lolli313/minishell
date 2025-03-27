/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/27 13:48:44 by Barmyh           ###   ########.fr       */
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

	handle_signals();
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
		if (mini->line)
		{
			if (mini->line->command && mini->line->command[0])
			{
				if (ft_strncmp("exit", mini->line->command[0], 5) == 0)
				{
					mini->exit_flag = 0;
					line_cleanup(mini);
					free(input);
					break;
				}
				ft_handle_redirections(mini);
				ft_handle_pipes(mini, envp);
				if (ft_is_builtin(mini->line->command))
					ft_handle_builtin(mini->line->command, mini);
				else
					ft_handle_external(mini, mini->line->command, envp);
				line_cleanup(mini);
			}
		}
		free(input);
	}
	free_env(mini->env);
	free(mini);
	return (42);
}
