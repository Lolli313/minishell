/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/03/27 07:21:04 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_pipes(t_line *cmd)
{
	int		i;
	t_line *tmp;

	i = -1;
	tmp = cmd;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_handle_pipes(t_mini *mini, char **envp)
{
	int	i;
	int	j;
	mini->nbr_of_pipes = ft_count_pipes(mini->line);
	pid_t cpid[mini->nbr_of_pipes + 1]; // childpid
	int pipefd[mini->nbr_of_pipes][2];
	t_line *cmd;

	cmd = mini->line;

	// create pipes
	i = 0;
	while (i < mini->nbr_of_pipes)
	{
		if (pipe(pipefd[i]) == -1)
			exit (1); // ERROR TODO
		i++;
	}
	// Fork child processes
	i = 0;
	while (i <= mini->nbr_of_pipes)
	{
		cpid[i] = fork();
		if (cpid[i] < 0)
			exit (1); // ERROR TODO
		if (cpid[i] == 0)
		{
			if (i == 0)
			{
				dup2(pipefd[i][1], STDOUT_FILENO);
			}
			else if (i == mini->nbr_of_pipes)
			{
				dup2(pipefd[i - 1][0], STDIN_FILENO); // read from prev pipe
			}
			else
			{
				dup2(pipefd[i - 1][0], STDIN_FILENO); // read from prev pipe
				dup2(pipefd[i][1], STDOUT_FILENO); // write to next pipe
			}
			j = 0;
			while (j < mini->nbr_of_pipes)
			{
				close(pipefd[j][0]);
				close(pipefd[j][1]);
				j++;
			}
			if (execve(cmd->command[0], cmd->command, envp) == -1)
				exit(1);
		}
		cmd = cmd->next;
		i++;
	}
	// Close all pipes in parent
	i = 0;
	while (i < mini->nbr_of_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	// wait for all child processes
	i = 0;
	while (i <= mini->nbr_of_pipes)
	{
		waitpid(cpid[i], NULL, 0);
		i++;
	}
}
