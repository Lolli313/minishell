/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/04/30 12:37:05 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_piping(t_mini *mini, t_line *current)
{
	(void)current;
	if (mini->pipe_in >= 0)
	{
		ft_safe_dup2(mini->pipe_in, STDIN);
		ft_close(mini->pipe_in);
		mini->pipe_in = -1;
	}
	ft_close(mini->fd);
	if (mini->pipe_out >= 0)
	{
		ft_safe_dup2(mini->pipe_out, STDOUT);
		ft_close(mini->pipe_out);
		mini->pipe_out = -1;
	}
}

int	ft_execute_child(t_mini *mini, t_line *current, pid_t *pids)
{
	int	exit_status;

	ft_piping(mini, current);
	ft_handle_redirections(mini, current);
	if (mini->skibidi == 1)
		exit(mini->exit_status);
	if (ft_is_builtin(current->command))
	{
		ft_handle_builtin(mini, current);
		line_cleanup(mini);
		free(pids);
		exit_status = mini->exit_status;
		free_mini(mini);
		exit(exit_status);
	}
	else
	{
		ft_handle_external(mini, current->command);
		line_cleanup(mini);
		free(pids);
		exit_status = mini->exit_status;
		free_mini(mini);
		exit(exit_status);
	}
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
		ft_close(mini->stdin);
		ft_close(mini->stdout);
		ft_piping(mini, current);
		mini->exit_status = ft_execute_child(mini, current, pids);
		free(pids);
		exit(mini->exit_status);
	}
	else
	{
		pids[i] = pid;
		ft_supersafe_close(mini->pipe_out);
	}
}

void	ft_piped_cmd(t_mini *mini, t_line *current, pid_t *pids, int i)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	mini->pipe_out = pipefd[1];
	mini->fd = pipefd[0];
	ft_fork_and_exe(mini, current, pids, i++);
	ft_close(pipefd[1]);
	ft_supersafe_close(mini->pipe_in);
	mini->pipe_in = pipefd[0];
}
