/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/21 20:15:24 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// unsure how to deal with 'ABC=hola' as input
// do we add that to the env variables or no

// TODO signals (CTRL + D and CTRL + \), free line related structures after every readline loop
// look into echo -n and how the syntax should be handled, look into how to handle the $?

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;
	(void)ac;
	(void)av;
//	(void)envp;
//	ft_printf("%s", *envp);
	while (1)
	{
		char	*line = readline(G "😭 minishell$ " RESET);
		mini.env = init_env(envp);
		parse_string(&mini, line);
//		free(line);
	}
	return (1);
}
