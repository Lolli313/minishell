/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/04/10 13:34:17 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper function for the parent process logic.
void	ft_handle_parent(t_mini *mini, t_line *current)
{
	(void)current;
	if (mini->pipe_in > 0)
    {
        ft_close(mini->pipe_in);
        mini->pipe_in = -1;
    }
}

void	ft_fork_and_exe(t_mini *mini, t_line *current)
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
		ft_execute_child(mini, current);
	}
	else
	{
	//	ft_handle_parent(mini, current);
		waitpid(pid, NULL, 0);
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
}
