/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:26:39 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/12 15:48:48 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_input(t_mini *mini, t_line *current, int prev_fd)
{
	if (prev_fd >= 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		ft_close(prev_fd);
	}
	if (current->redirect && current->redirect->heredoc_fd != STDIN_FILENO)
	{
		if (current->redirect->type == LIMITER)
		{
			if (dup2(current->redirect->heredoc_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 heredoc_fd");
				exit(EXIT_FAILURE);
			}
		}
		else
			ft_handle_redirections(mini);
		ft_close(current->redirect->heredoc_fd);
		current->redirect->heredoc_fd = -1;
	}
}

void	ft_redir_output(t_line *current, int pipe_fds[2])
{
	if (current->next)
	{
		ft_close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe_fd -> STDOUT");
			exit(EXIT_FAILURE);
		}
		ft_close(pipe_fds[1]);
	}
}

void	ft_restore_std_fds(t_mini *mini)
{
	ft_safe_dup2(mini->stdin, STDIN);
	ft_safe_dup2(mini->stdout, STDOUT);
}

void	ft_close(int fd)
{
	if (fd >= 0)
	{
		close(fd);
	}
}

void	ft_safe_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2 failed");
		ft_close(oldfd);
		exit(EXIT_FAILURE);
	}
}

