/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:55:22 by aakerblo          #+#    #+#             */
/*   Updated: 2025/05/05 13:23:12 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_handle_sigint(int signals)
{
	if (signals == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_skip || g_skip == 130 || g_skip == 2)
		{
			rl_redisplay();
		}
	}
	else if (signals == SIGINT && g_skip)
	{
		g_skip = 0;
		printf("\n");
	}
	g_skip = 130;
}

void	ft_handle_heredoc_sig(int signals)
{
	if (signals == SIGINT)
	{
		g_skip = 0;
		close(STDIN_FILENO);
		exit(130);
	}
}

void	ft_handle_function_signals(int signals)
{
	if (signals == SIGQUIT)
	{
		g_skip = 0;
		ft_close(STDIN);
		exit(1);
	}
}
