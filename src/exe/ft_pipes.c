/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/04/14 12:22:39 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_child(t_mini *mini, t_line *current)
{
	if (mini->pipe_in >= 0)
	{
		ft_safe_dup2(mini->pipe_in, STDIN);
		ft_close(mini->pipe_in);
		mini->pipe_in = -1;
	}
	if (current->next)
	{
		//ft_close(mini->pipe_in);
		ft_safe_dup2(mini->pipe_out, STDOUT);
		ft_close(mini->pipe_out);
		mini->pipe_out = -1;
	}
	if (current->redirect && current->redirect->heredoc_fd != STDIN)
	{
		if (current->redirect->type == LIMITER)
			ft_safe_dup2(current->redirect->heredoc_fd, STDIN);
		else
			ft_handle_redirections(mini);
		ft_close(current->redirect->heredoc_fd);
		current->redirect->heredoc_fd = -1;
	}
	mini->line = current;
	ft_handle_redirections(mini);
	if (ft_is_builtin(current->command))
	{
		ft_handle_builtin(mini);
		exit(mini->exit_status);
	}
	else
	{
		ft_handle_external(mini, current->command);
		exit(mini->exit_status);
	}
		
	if (mini->pipe_out >= 0)
		ft_close(mini->pipe_out);
	if (mini->pipe_in >= 0)
	{
		ft_close(mini->pipe_in);
	}
	signal(SIGPIPE, &ft_handle_sigpipe);
	exit(EXIT_SUCCESS);
}

void	ft_fork_and_exe(t_mini *mini, t_line *current, pid_t *pids, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		ft_execute_child(mini, current);
	}
	else
	{
		pids[i] = pid;
	}
}

static int ft_wait(t_mini *mini, pid_t *pids, int i)
{

	int status;
	int	j;

	j = 0;

	while (j < i)
	{
        waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mini->exit_status = 128 + WTERMSIG(status);
		j++;
	}
	return (mini->exit_status);
}

void	ft_execute_pipeline(t_mini *mini)
{
	t_line	*current;
	int		pipefd[2];
	pid_t	pids[mini->nbr_of_pipes + 1];
	int i = 0;

	current = mini->line;
	while (current)
	{
		if (current->redirect && current->redirect->type == LIMITER)
			ft_pipe_heredoc(mini, current);
		if (current->next)
		{
			if (pipe(pipefd) == -1)
				exit(EXIT_FAILURE);
			mini->pipe_out = pipefd[1];
			ft_fork_and_exe(mini, current, pids, i++);
			ft_close(pipefd[1]);
			mini->pipe_in = pipefd[0];
		}
		else
		{
			mini->pipe_out = -1;
			ft_fork_and_exe(mini, current, pids, i++);
		}
		current = current->next;
	}
	if (mini->pipe_in >= 0)
		ft_close(mini->pipe_in);
	ft_wait(mini, pids, i);
}
