/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:00:33 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/23 13:55:12 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_child(t_mini *mini, t_re *redir, int *pipefd)
{
	char	*line;
	char	*tmp;
	int		i;
	int		line_count;

	line_count = 1;
	ft_close(pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document at line");
			printf(" %d", line_count);
			printf(" delimited by end-of-file");
			printf(" (wanted `%s')\n", redir->str);
			free(line);
			break ;
		}
		else if (strncmp(line, redir->str, ft_strlen(redir->str)) == 0)
		{
			free(line);
			break ;
		}
		line_count++;
		i = 0;
		tmp = line;
		while (tmp && tmp[i])
		{
			if (tmp[i] == '$')
			tmp = handle_dollar_sign(mini, tmp, &tmp[i], &i);
			else
			i++;
		}
		write(pipefd[1], tmp, ft_strlen(tmp));
		write(pipefd[1], "\n", 1);
		free(line);
	}
}

void	ft_handle_heredoc(t_mini *mini, t_re *redir)
{
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[0]);
		ft_heredoc_child(mini, redir, pipefd);
		ft_close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		redir->heredoc_fd = pipefd[0];
		ft_close(pipefd[1]);
		waitpid(pid, NULL, 0);
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
