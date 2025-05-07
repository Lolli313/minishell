/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:00:33 by Barmyh            #+#    #+#             */
/*   Updated: 2025/05/07 09:34:13 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_term(t_mini *mini, char *line)
{
	if (g_skip == 130)
	{
		mini->hd_count++;
		mini->exit_status = 130;
		return (1);
	}
	if (line == NULL)
		return (1);
	return (0);
}

int	ft_heredoc_child(t_mini *mini, t_re *redir, int *pipefd)
{
	char	*line;
	int		i;
	int		count;

	prepare_heredoc(&count);
	while (1)
	{
		line = handle_heredoc_line(mini, redir, count);
		if (ft_check_term(mini, line))
			break ;
		count++;
		i = 0;
		while (line && line[i])
		{
			if (line[i] == '$')
				line = handle_dollar_sign(mini, line, &line[i], &i);
			else
				i++;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	handle_signals();
	return (count + 1);
}

int	ft_handle_heredoc(t_mini *mini, t_re *redir)
{
	int	pipefd[2];
	int	count;

	count = 0;
	pipe(pipefd);
	count = ft_heredoc_child(mini, redir, pipefd);
	ft_close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (count);
}

void	ft_pipe_heredoc(t_mini *mini, t_line *current)
{
	t_re	*redir;

	if (current->redirect)
	{
		redir = current->redirect;
		while (redir)
		{
			if (redir->type == LIMITER)
			{
				ft_handle_heredoc(mini, redir);
				if (g_skip == 130)
				{
					mini->skibidi = 1;
					break ;
				}
				current->redirect->heredoc_fd = redir->heredoc_fd;
			}
			redir = redir->next;
		}
	}
}

void	ft_execute_heredoc(t_mini *mini)
{
	t_re	*redir;

	redir = mini->line->redirect;
	while (redir)
	{
		if (redir->type == LIMITER)
		{
			ft_handle_heredoc(mini, redir);
			if (g_skip == 130)
				break ;
		}
		redir = redir->next;
	}
}
