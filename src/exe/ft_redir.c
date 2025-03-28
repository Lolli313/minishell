/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:26:21 by Barmyh            #+#    #+#             */
/*   Updated: 2025/03/28 09:54:44 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
> output operator:
overwrites
>> output append:

< input operator
sort < my.txt will sort lines in the txt file


| Redirection Type       | File Open Mode                      | Behavior                                 |
|------------------ -----|-------------------------------------|------------------------------------------|
| `<` (Input)            | `O_RDONLY`                          | Opens file for reading (stdin)          |
| `>` (Overwrite Output) | `O_WRONLY | O_CREAT | O_TRUNC`      | Opens or creates file, truncates if exists |
| `>>` (Append Output)   | `O_WRONLY | O_CREAT | O_APPEND`     | Opens or creates file, appends if exists |
| `<<` (Heredoc)         | `pipe(fd)`                          | Stores input in a pipe instead of a file |
*/

void ft_handle_redirections(t_mini *mini)
{
    t_re *redir = mini->line->redirect;
    
    while (redir)
    {
        if (redir->type == INFILE)
            ft_handle_input_redir(redir);
        else if (redir->type == OUTFILE || redir->type == APPEND_OUTFILE)
            ft_handle_output_redir(redir);
        else if (redir->type == LIMITER)
            ft_handle_here_doc(redir);
        redir = redir->next;
    }
}

int ft_handle_input_redir(t_re *redir)
{
    int fd;

    if (!redir->str)
    {
        perror("Redirection is NULL");
        return (-1);
    }
    fd = open(redir->str, O_RDONLY);
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        close (fd);
        return (-1);
    }
    close (fd);
    return (0);
}

int ft_handle_output_redir(t_re *redir)
{
    int fd;
	
    if (redir->type == OUTFILE)
    {
        fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0700);
        if (fd == -1)
        {
            perror("Fail");
            return (-1);
        }
    }
    else
    {
        fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0700);
        if (fd == -1)
        {
            perror("Fail");
            return (-1);
        }
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2 error");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int ft_handle_here_doc(t_re *redir)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line || strncmp(line, redir->str, ft_strlen(redir->str)) == 0)
            break;
		ft_putendl_fd(redir->str, STDIN_FILENO);
        free(line);
    }
    free(redir->str);
    return (0);
}