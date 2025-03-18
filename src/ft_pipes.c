/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/03/18 10:41:51 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_count_pipes(t_line *line)
{
	t_line	*tmp;
	int	i;

	tmp = line;
	i = 0;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return i;
}

void	ft_handle_pipes(t_mini *mini)
{
	int	i;
	int	j;
	pid_t cpid[mini->nbr_of_pipes + 1]; // childpid
	int pipefd[mini->nbr_of_pipes][2]; 

	mini->nbr_of_pipes = ft_count_pipes(mini->line);
	// create pipes
	i = 0;
	while (i < mini->nbr_of_pipes)
	{
		if (pipe(pipefd[i]) == -1)
			exit; // ERROR TODO
		i++;
	}
	// Fork child processes
	i = 0;
	while (i <= mini->nbr_of_pipes)
	{
		cpid[i] = fork();
		if (cpid[i] < 0)
			exit; // ERROR TODO
		if (cpid[i] == 0)
		{
			if (i == 0)
			{
				dup2(pipefd[i][1], STDOUT_FILENO);
			}
			else if (i == mini->nbr_of_pipes)
			{
				dup2(pipefd[i][0], STDIN_FILENO);
			}
			else
			{
				dup2(pipefd[i - 1][0], STDIN_FILENO);
				dup2(pipefd[i][1], STDOUT_FILENO);
			}
			j = 0;
			if (j < mini->nbr_of_pipes)
			{
				close(pipefd[j][0]);
				close(pipefd[j][1]);
				j++;
			}
			execve(mini->line->command[0], mini->line->command, ft_function(envp));
			exit(1);
		}
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
	return (0);
}

//        int execve(const char *pathname, char *const _Nullable argv[],
// char *const _Nullable envp[]);
