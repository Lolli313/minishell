/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:26:39 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/08 08:46:51 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_input(t_mini *mini, t_line *current, int prev_fd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (current->redirect && current->redirect->heredoc_fd != -1)
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
		close(current->redirect->heredoc_fd);
		current->redirect->heredoc_fd = -1;
	}
}

void	ft_redir_output(t_line *current, int pipe_fds[2])
{
	if (current->next)
	{
		close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe_fd -> STDOUT");
			exit(EXIT_FAILURE);
		}
		close(pipe_fds[1]);
	}
}

void	ft_execute_child(t_mini *mini, t_line *current, int prev_fd,
		int pipe_fds[2])
{
	ft_redir_input(mini, current, prev_fd);
	ft_redir_output(current, pipe_fds);
	mini->line = current;
	ft_handle_redirections(mini);
	if (ft_is_builtin(current->command))
		ft_handle_builtin(mini);
	else
		ft_handle_external(mini, current->command);
	exit(EXIT_SUCCESS);
}

void	ft_restore_std_fds(t_mini *mini)
{
	if (dup2(mini->stdin, STDIN_FILENO) == -1)
	{
		perror("dup2 STDIN");
		exit(EXIT_FAILURE);
	}
	if (dup2(mini->stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2 STDOUT");
		exit(EXIT_FAILURE);
	}
	close(mini->stdin);
	close(mini->stdout);
}
