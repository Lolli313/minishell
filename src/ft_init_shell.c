/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:08:56 by fmick             #+#    #+#             */
/*   Updated: 2025/02/28 11:18:09 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_signal_handler(int sig, siginfo_t *info)
{
	// minitalk magic
}

void	ft_shell(int ac, char **av)
{
	if (ac != 1 || strcmp(av[0]), "./minishell" != 0)
	{
		printf(R "Wrong input: ./minishell\n" RESET);
		return ;
	}
	else
	{
		// ?????????????;
		// signal (smth, &ft_signal_handler);
	}
}
