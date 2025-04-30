/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:36:12 by fmick             #+#    #+#             */
/*   Updated: 2025/04/30 11:49:33 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_std_fds(t_mini *mini)
{
	ft_safe_dup2(mini->stdin, STDIN);
	ft_safe_dup2(mini->stdout, STDOUT);
}

void	ft_safe_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2 failed");
		if (oldfd >= 0)
			ft_close(oldfd);
		exit(EXIT_FAILURE);
	}
}

int	ft_wait_util(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (131);
	}
	else if (WTERMSIG(status) == SIGINT)
		return (130);
	else
		return (128 + WTERMSIG(status));
}

int	ft_wait(t_mini *mini, pid_t *pids, int i)
{
	int	status;
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
		{
			mini->exit_status = WEXITSTATUS(status);
			if (j == i - 1 && mini->exit_status == 131)
				ft_putstr_fd("Quit (core dumped)\n", 2);
		}
		else if (WIFSIGNALED(status))
			mini->exit_status = ft_wait_util(status);
		j++;
	}
	return (mini->exit_status);
}
