/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/04 16:20:58 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
//	ft_printf("%s", *envp);
	char	*line = readline("bash-5.1$ ");
	parse_string(line);
//	ft_printf("%s\n", line);
//	init_env(envp);
	return (1);
}
