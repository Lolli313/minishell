/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:00:33 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/06 11:00:11 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_heredoc_child(t_re *redir, int *pipefd)
{
    char *line;

    close(pipefd[0]); 
    while (1)
    {
		line = readline("> ");
        if (!line || strncmp(line, redir->str, ft_strlen(redir->str)) == 0)
        {
            free(line);
            break;
        }
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1); 
        free(line);
    }
	close(pipefd[1]);
}

void ft_handle_heredoc(t_mini *mini, t_re *redir)
{
    int pipefd[2];
	pid_t pid;

	(void)mini;
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		ft_heredoc_child(redir, pipefd);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
        redir->heredoc_fd = pipefd[0];
        close(pipefd[1]);
        waitpid(pid, NULL, 0);
	}
}

void    ft_pipe_heredoc(t_mini *mini, t_line *current)
{
    if (current->redirect)
    {
        t_re *redir = current->redirect;
        while (redir)
        {
            if (redir->type == LIMITER) // Heredoc
            {
                ft_handle_heredoc(mini, redir);
				if (redir->heredoc_fd == -1)
				{
					perror("Heredoc FD error");
					exit(EXIT_FAILURE);
				}
				if (current->redirect->heredoc_fd == -1)
                		current->redirect->heredoc_fd = redir->heredoc_fd;
            	ft_printf("Assigning heredoc_fd %d to command: %s\n", redir->heredoc_fd, current->command[0]);
            }
            redir = redir->next;
        }
    }
}
