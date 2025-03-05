/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:39:10 by fmick             #+#    #+#             */
/*   Updated: 2025/03/05 15:40:13 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	int		exit;

	exit = 1;
	signal(SIGINT, &ft_handle_sigint);
	(void)ac;
	(void)av;
	ft_init_env(envp);
	while (exit == 1)
	{
		input = readline(G "😭 minishell$ " RESET);
		input = readline(R "🥵 minishell$ " RESET);
		if (*input)
			add_history(input);
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
	}
	return (0);
}
