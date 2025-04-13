/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/04/13 18:15:15 by Barmyh           ###   ########.fr       */
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
	//	ft_close(mini->pipe_in);
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
//	ft_handle_redirections(mini);
	if (ft_is_builtin(current->command))
		ft_handle_builtin(mini);
	else
		ft_handle_external(mini, current->command);
	if (mini->pipe_out >= 0)
        ft_close(mini->pipe_out);
    if (mini->pipe_in >= 0)
	{
        ft_close(mini->pipe_in);
	}
	exit(EXIT_SUCCESS);
}

void	ft_fork_and_exe(t_mini *mini, t_line *current)
{
	pid_t	pids[mini->nbr_of_pipes];
	pid_t	pid;
	int i;
	int j;

	i = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		ft_execute_child(mini, current);
	}
	else
	{
		pids[i] = pid;
		i++;
	}
	j = 0;
	while (j < i)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
}

void	ft_execute_pipeline(t_mini *mini)
{
	t_line	*current;
	int pipefd[2];

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
            ft_fork_and_exe(mini, current);
			ft_close(pipefd[1]);
            mini->pipe_in = pipefd[0];
        }
        else
        {
            mini->pipe_out = -1;
            ft_fork_and_exe(mini, current);
        }
        current = current->next;
    }
	if (mini->pipe_in >= 0)
		ft_close(mini->pipe_in);
}
