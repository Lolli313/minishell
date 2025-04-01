/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:00:33 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/01 11:39:07 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_prepare_heredocs(t_mini *mini)
{
    t_re *redir;
    int i;
    char *line;

    i = 0;
    redir = mini->line->redirect;
    while (redir)
    {
        if (redir->type == LIMITER)
        {
            printf("Preparing heredoc: pipe index = %d\n", i);
            while (1)
            {
                line = readline("> ");
				if (!line) // Handle EOF (CTRL+D)
                {
                    perror("readline");
                    break;
                }
                if (ft_strcmp(line, redir->str) == 0) // delimiter
                {
                    free(line);
                    break;
                }
                ft_putendl_fd(line, mini->hd_pipefd[i][1]); 
                free(line); 
            }
            close(mini->hd_pipefd[i][1]);
            i++;
        }
        redir = redir->next;
    }
}

void ft_handle_here_doc(t_mini *mini, t_re *redir, int index)
{
    char *line;

    if (pipe(mini->hd_pipefd[index]) == -1)
    {
        perror("pipe");
        return;
    }

    while (1)
    {
        line = readline("> ");
		if (!line) // Handle EOF (CTRL+D)
        {
			//signal handler
            perror("readline");
            break;
        }
        if (ft_strcmp(line, redir->str) == 0) // delimiter
        {
            free(line);
			return;
        }
        ft_putendl_fd(line, mini->hd_pipefd[index][1]); // Write to the write end of the pipe
        free(line);
    }

    close(mini->hd_pipefd[index][1]);
}

void ft_redirect_heredoc_stdin(t_mini *mini)
{
    int last_pipe;

    if (mini->hd_count > 0)
    {
        last_pipe = mini->hd_count - 1;
        printf("Redirecting heredoc: last_pipe = %d, fd = %d\n", last_pipe, mini->hd_pipefd[last_pipe][0]);
        if (dup2(mini->hd_pipefd[last_pipe][0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            return;
        }
        close(mini->hd_pipefd[last_pipe][0]);
    }
}

void ft_allocate_heredoc_pipes(t_mini *mini)
{
    int i;

    mini->hd_pipefd = malloc(sizeof(int *) * mini->hd_count);
    if (!mini->hd_pipefd)
    {
        perror("malloc");
        exit(1);
    }
    i = 0;
    while (i < mini->hd_count)
    {
        mini->hd_pipefd[i] = malloc(sizeof(int) * 2);
        if (!mini->hd_pipefd[i])
        {
            perror("malloc");
            exit(1);
        }
        if (pipe(mini->hd_pipefd[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
        printf("Allocated pipe: index = %d, read_fd = %d, write_fd = %d\n", i, mini->hd_pipefd[i][0], mini->hd_pipefd[i][1]);
        i++;
    }
}

void ft_cleanup_heredocs(t_mini *mini)
{
    int i;

    if (mini->hd_pipefd)
    {
        i = 0;
        while (i < mini->hd_count)
        {
            close(mini->hd_pipefd[i][0]); // Close read end
            close(mini->hd_pipefd[i][1]);
            free(mini->hd_pipefd[i]);
            i++;
        }
        free(mini->hd_pipefd);
        mini->hd_pipefd = NULL;
    }
    mini->hd_count = 0;
}

int ft_count_heredocs(t_re *redir)
{
    int count;

    count = 0;
    while (redir)
    {
        if (redir->type == LIMITER)
            count++;
        redir = redir->next;
    }
    return (count);
}
