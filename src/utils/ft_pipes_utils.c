/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:36:12 by fmick             #+#    #+#             */
/*   Updated: 2025/04/17 11:23:28 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_supersafe_close(int fd)
{
	if (fd >= 0)
	{
		ft_close(fd);
		fd = -1;
	}
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

int	ft_wait(t_mini *mini, pid_t *pids, int i)
{
	int	status;
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
