/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/04/08 20:03:24 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper function for the parent process logic.
void	ft_handle_parent(t_line *current, int *prev_fd, int pipe_fds[2])
{
	if (*prev_fd != -1)
	{
		ft_close(*prev_fd);
		*prev_fd = -1;  // Mark it as closed
	}

	if (current->next)
	{
		if (pipe_fds[1] != -1)
		{
			ft_close(pipe_fds[1]);  // Only close if it's a pipeline
			pipe_fds[1] = -1;  // Prevent double close
		}
		*prev_fd = pipe_fds[0];  // Save read end for next command
	}
	else
	{
		*prev_fd = -1;  // No next command, no need to store fd
	}
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
	{
		ft_execute_child(mini, current, prev_fd, pipe_fds);
	}
	else
	{
		ft_handle_parent(current, &prev_fd, pipe_fds);
//		waitpid(pid, NULL, 0);
	}
}

void	ft_execute_pipeline(t_mini *mini)
{
	t_line	*current;
	int		pipefd[2];
	int		prev_fd;

	current = mini->line;
	prev_fd = -1;

	while (current)
	{
		ft_pipe_heredoc(mini, current);
		if (current->next && pipe(pipefd) == -1)
			exit(EXIT_FAILURE);
		ft_fork_and_exe(mini, current, prev_fd, pipefd);
		if (current->next)
		{
			ft_close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		else
			prev_fd = -1;
		current = current->next;
	}
	current = mini->line;
	while (current)
	{
		wait(NULL);
		current = current->next;
	}
	ft_close(prev_fd);
	//if (prev_fd != STDIN_FILENO && prev_fd != -1)
	//{
	//	ft_close(prev_fd);
	//	prev_fd = -1;
	//}
		
}
