/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:44:57 by fmick             #+#    #+#             */
/*   Updated: 2025/04/14 12:17:53 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_global = 0;

void	ft_handle_sigpipe(int signal)
{
	if (SIGPIPE == signal)
	{
		ft_putendl_fd("Broken pipe\n", 2);
		exit (1);
	}
}

void	ft_handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_global++;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	signal(SIGINT, &ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
