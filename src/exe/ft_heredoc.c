/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:00:33 by Barmyh            #+#    #+#             */
/*   Updated: 2025/05/05 12:36:38 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc_child(t_mini *mini, t_re *redir, int *pipefd)
{
	char	*line;
	int		i;
	int		count;

	prepare_heredoc(&count, &i, pipefd);
	while (1)
	{
		line = handle_heredoc_line(mini, redir, count);
		if (line == NULL)
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
	return (count + 1);
}

void	ft_handle_heredoc(t_mini *mini, t_re *redir)
{
	int		pipefd[2];
	pid_t	pid;
	int		count;
	int		status;

	count = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[0]);
		count = ft_heredoc_child(mini, redir, pipefd);
		ft_close(pipefd[1]);
		exit(count);
	}
	else
	{
		redir->heredoc_fd = pipefd[0];
		ft_close(pipefd[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			mini->hd_count += WEXITSTATUS(status);
			if (WEXITSTATUS(status) == 130)
			{
				mini->skibidi = 3;
				mini->exit_status = 130;
			}
		}
		handle_signals();
	}
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
		}
		redir = redir->next;
	}
}
