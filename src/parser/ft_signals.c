/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:44:57 by fmick             #+#    #+#             */
/*   Updated: 2025/04/23 16:52:13 by aakerblo         ###   ########.fr       */
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

void	ft_handle_heredoc_sig(int signals)
{
	if (signals == SIGINT)
	{
		g_skip = false;
		printf("\n");
		close(STDIN_FILENO);
		exit(130);
	}
}

void	ft_handle_function_signals(int signals)
{
	if (signals == SIGQUIT)
	{
		g_skip = false;
		printf("Quit (core dumped)\n");
		ft_putendl_fd("Quit (core dumped)", 2);
		ft_close(STDIN);
		exit(1);
	}
}

void	handle_heredoc_sig(void)
{
	signal(SIGINT, &ft_handle_heredoc_sig);
}

void	handle_function_signals(void)
{
	signal(SIGQUIT, &ft_handle_function_signals);
}

void	handle_signals(void)
{
	signal(SIGINT, &ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
