/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/04/08 08:59:41 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper function for the parent process logic.
void	ft_handle_parent(t_line *current, int *prev_fd, int pipe_fds[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
		close(pipe_fds[1]);
	if (current->next)
	{
		close(pipe_fds[1]);
		*prev_fd = pipe_fds[0];
	}
	else
		*prev_fd = -1;
}

void	ft_fork_and_exe(t_mini *mini, t_line *current, int prev_fd,
		int pipe_fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_execute_child(mini, current, prev_fd, pipe_fds);
	else
	{
		ft_handle_parent(current, &prev_fd, pipe_fds);
		waitpid(pid, NULL, 0);
	}
}

void	ft_execute_pipeline(t_mini *mini)
{
	t_line	*current;
	int		pipe_fds[2];
	int		prev_fd;

	current = mini->line;
	prev_fd = -1;
	while (current)
	{
		ft_pipe_heredoc(mini, current);
		if (current->next && pipe(pipe_fds) == -1)
			exit(EXIT_FAILURE);
		ft_fork_and_exe(mini, current, prev_fd, pipe_fds);
		if (current->next)
		{
			close(pipe_fds[1]);
			prev_fd = pipe_fds[0];
		}
		else
			prev_fd = -1;
		current = current->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
}
