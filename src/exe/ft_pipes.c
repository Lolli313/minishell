/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/04/01 14:33:41 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_close_all_pipes(t_mini *mini)
{
    int	i;
	
	i = 0;
    while (i < mini->nbr_of_pipes)
    {
        close(mini->pipefd[i][0]);
        close(mini->pipefd[i][1]);
        i++;
    }
}

void ft_cleanup_pipes(t_mini *mini)
{
    int i;

    i = 0;
    if (mini->pipefd)
    {
        while (i < mini->nbr_of_pipes)
        {
            free(mini->pipefd[i]);
            i++;
        }
        free(mini->pipefd);
        mini->pipefd = NULL;
    }
    if (mini->cpid)
    {
        free(mini->cpid);
        mini->cpid = NULL;
    }
}

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

void ft_allocate_pipes(t_mini *mini)
{
    int i;

    i = 0;
    mini->pipefd = malloc(sizeof(int *) * mini->nbr_of_pipes);
    while (i < mini->nbr_of_pipes)
    {
        mini->pipefd[i] = malloc(sizeof(int) * 2);
        if (!mini->pipefd[i])
        {
            perror("malloc");
            exit(1);
        }
        if (pipe(mini->pipefd[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
        i++;
    }
}

void ft_fork_processes(t_mini *mini)
{
    int i;
    t_line *cmd;

    i = 0;
    cmd = mini->line;
    while (i <= mini->nbr_of_pipes)
    {
        if (!cmd)
        {
            perror("Command is NULL during iteration");
            exit(1);
        }
        mini->cpid[i] = fork();
        if (mini->cpid[i] < 0)
        {
            perror("fork");
            exit(1);
        }
        if (mini->cpid[i] == 0) // Child process
        {
            ft_execute_child(mini, cmd, i);
        }
        cmd = cmd->next;
        i++;
    }
}

void ft_execute_child(t_mini *mini, t_line *cmd, int i)
{
    char *full_path;

    full_path = check_external(mini->env, cmd->command[0]);
    if (i == 0) // First command
        dup2(mini->pipefd[i][1], STDOUT_FILENO);
    else if (i == mini->nbr_of_pipes) // Last command
        dup2(mini->pipefd[i - 1][0], STDIN_FILENO);
    else // Middle command
    {
        dup2(mini->pipefd[i - 1][0], STDIN_FILENO);
        dup2(mini->pipefd[i][1], STDOUT_FILENO);
    }
	ft_close_all_pipes(mini);
    ft_handle_redirections(mini);
    if (execve(full_path, cmd->command, mini->env_array) == -1)
    {
        perror("execve");
        free(full_path);
        exit(1);
    }
}

void ft_handle_pipes(t_mini *mini)
{
    int i;

    mini->nbr_of_pipes = ft_count_pipes(mini->line);
    ft_allocate_pipes(mini);
    mini->cpid = malloc(sizeof(pid_t) * (mini->nbr_of_pipes + 1));
    if (!mini->cpid)
    {
        perror("malloc");
        exit(1);
    }
    ft_fork_processes(mini);
	ft_close_all_pipes(mini);
    i = 0;
    while (i <= mini->nbr_of_pipes)
    {
        waitpid(mini->cpid[i], NULL, 0);
        i++;
    }
    ft_cleanup_pipes(mini);
}
