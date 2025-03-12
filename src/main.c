/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:39:10 by fmick             #+#    #+#             */
/*   Updated: 2025/03/12 15:29:12 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_mini	*mini;

	signal(SIGINT, &ft_handle_sigint);
	(void)ac;
	(void)av;
	
	mini = (t_mini *)malloc(sizeof(t_mini));
	mini->exit_flag = 1;
	mini->env = ft_init_env(envp);
	while (mini->exit_flag == 1)
	{
		input = readline(G "😭 minishell$ " RESET);
		if (*input)
		{
			add_history(input);
			ft_env(mini->env);
			printf("Received input: %s\n", input);
		}
		if (strcmp(input, "exit") == 0)
		{
			mini->exit_flag = 0;
			free(input);
			break;
		}
	}
	return (0);
}
