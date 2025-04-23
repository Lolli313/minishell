/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:44:57 by fmick             #+#    #+#             */
/*   Updated: 2025/04/23 12:31:44 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_skip = false;

void	ft_handle_sigint(int signals)
{
	if (signals == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_skip)
		{
			rl_redisplay();
		}
	}
	else if (signals == SIGINT && g_skip == true)
	{
		g_skip = false;
		printf("\n");
	}
}

void	ft_handle_sigquit(int signals)
{
	if (signals == SIGQUIT && g_skip)
	{
		signal(SIGQUIT, SIG_IGN);
		printf("Quit (core dumped)\n");
		return ;
	}
	else if (signals == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
	}
}

void	handle_signals(void)
{
	signal(SIGINT, &ft_handle_sigint);
	signal(SIGQUIT, &ft_handle_sigquit);
}
