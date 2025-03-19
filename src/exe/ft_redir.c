/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:26:21 by Barmyh            #+#    #+#             */
/*   Updated: 2025/03/19 07:46:09 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

int ft_handle_input_redir(t_redirect *redir)
{
    int fd;

    fd = open(redir->str, O_RDONLY);
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        // error dup2
        close (fd);
        return (-1);
    }
    close (fd);
    return (0);
}
int ft_handle_output_redir(t_redirect *redir)
{
    int fd;
    if (redir->type == RE_OUTPUT)
        fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else
        fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
    
    if (fd == -1)
    {
        // open error
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        // dup2 error
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int ft_handle_here_doc(t_redirect *redir)
{
    int fd;
    char *line;

    fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        // open error

    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, redir->str) == 0)
            break;
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(line);
    close(fd);
    
    fd = open(".heredoc_tmp", O_RDONLY);
    if (fd == -1)
        // open error
    if (dup2(fd, STDIN_FILENO) == -1)
        // dup2 error
    close(fd);
    return (0);
}

int ft_exe_redir(t_redirect *redir)
{
    while (redir)
    {
        if (redir->type == RE_INPUT)
        {
            if (handle_input_redirection(redir) == -1)
                return (-1);
        }
        else if (redir->type == RE_OUTPUT || redir->type == RE_APPEND)
        {
            if (handle_output_redirection(redir) == -1)
                return (-1);
        }
        else if (redir->type == HERE_DOC)
        {
            if (handle_heredoc(redir) == -1)
                return (-1);
        }
        redir = redir->next;
    }
    return (0);
}

