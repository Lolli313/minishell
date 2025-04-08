/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:00:33 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/08 15:39:33 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_child(t_mini *mini, t_re *redir, int *pipefd)
{
	char	*line;
	char	*read_line;
	int		i;

	close(pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || strncmp(line, redir->str, ft_strlen(redir->str)) == 0)
		{
			free(line);
			break ;
		}
		i = 0;
		read_line = line;
		while (read_line && read_line[i])
		{
			if (read_line[i] == '$')
				read_line = handle_dollar_sign(mini, read_line, &read_line[i],
						&i);
			else
				i++;
		}
		write(pipefd[1], read_line, ft_strlen(read_line));
		write(pipefd[1], "\n", 1);
	}
	close(pipefd[1]);
}

void	ft_handle_heredoc(t_mini *mini, t_re *redir)
{
	int		pipefd[2];
	pid_t	pid;

	(void)mini;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		ft_heredoc_child(mini, redir, pipefd);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		redir->heredoc_fd = pipefd[0];
		close(pipefd[1]);
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
				if (redir->heredoc_fd == -1)
				{
					perror("Heredoc FD error");
					exit(EXIT_FAILURE);
				}
				if (current->redirect->heredoc_fd == -1)
					current->redirect->heredoc_fd = redir->heredoc_fd;
			}
			redir = redir->next;
		}
	}
}

void	ft_execute_heredoc(t_mini *mini)
{
	if (mini->line->redirect && mini->line->redirect->type == LIMITER)
	{
		ft_pipe_heredoc(mini, mini->line);
		if (mini->line->redirect->heredoc_fd != -1)
		{
			if (dup2(mini->line->redirect->heredoc_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 heredoc_fd -> STDIN");
				close(mini->line->redirect->heredoc_fd);
				exit(EXIT_FAILURE);
			}
			close(mini->line->redirect->heredoc_fd);
			mini->line->redirect->heredoc_fd = -1;
		}
	}
}
