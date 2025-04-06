/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:35:11 by fmick             #+#    #+#             */
/*   Updated: 2025/04/06 11:06:35 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setup_input_redirection(t_mini *mini, t_line *current, int prev_fd)
{
	if (prev_fd != -1)
	{
        if (dup2(prev_fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
		close(prev_fd);
	}
	if (current->redirect && current->redirect->heredoc_fd != -1)
	{
		if (current->redirect->type == LIMITER)
		{
        	if (dup2(current->redirect->heredoc_fd, STDIN_FILENO) == -1)
        	{
        	    perror("dup2 heredoc_fd");
        	    exit(EXIT_FAILURE);
        	}
		}
		else
			ft_handle_redirections(mini);
		close(current->redirect->heredoc_fd);
		current->redirect->heredoc_fd = -1;
	}
}

void    execute_child(t_mini *mini, t_line *current, int prev_fd, int pipe_fds[2])
{
    if (prev_fd != -1)
    {
        if (dup2(prev_fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(prev_fd);
    }
	if (current->redirect && current->redirect->heredoc_fd != -1)
    {
		if (current->redirect->type == LIMITER)
		{
        	if (dup2(current->redirect->heredoc_fd, STDIN_FILENO) == -1)
        	{
        	    perror("dup2 heredoc_fd");
        	    exit(EXIT_FAILURE);
        	}
		}
		else
			ft_handle_redirections(mini);
        close(current->redirect->heredoc_fd);
        current->redirect->heredoc_fd = -1; // Mark as used
    }
    if (current->next)
    {
        close(pipe_fds[0]); 
        if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
        {
            perror("dup2 pipe_fd -> STDOUT");
            exit(EXIT_FAILURE);
        }
        close(pipe_fds[1]);
    }
    mini->line = current;
	ft_handle_redirections(mini);
    if (ft_is_builtin(current->command))
        ft_handle_builtin(mini);
    else
        ft_handle_external(mini, current->command);
    exit(EXIT_SUCCESS);
}

// Helper function for the parent process logic.
void    handle_parent(t_line *current, int *prev_fd, int pipe_fds[2])
{
    if (*prev_fd != -1)
        close(*prev_fd);
    if (current->next)
        close(pipe_fds[1]);
    if (current->next)
        *prev_fd = pipe_fds[0];
    else
        *prev_fd = -1;
}



void    ft_execute_pipeline(t_mini *mini)
{
    t_line *current = mini->line;
    int pipe_fds[2];
    int prev_fd = -1;
    pid_t pid;

    while (current)
    {
        ft_pipe_heredoc(mini, current);
        if (current->next && pipe(pipe_fds) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
            execute_child(mini, current, prev_fd, pipe_fds);
        else // Parent process.
        {
            handle_parent(current, &prev_fd, pipe_fds);
            waitpid(pid, NULL, 0);
        }
        current = current->next;
    }
    if (prev_fd != -1)
        close(prev_fd);
}
