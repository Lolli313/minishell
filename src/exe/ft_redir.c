/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:26:21 by Barmyh            #+#    #+#             */
/*   Updated: 2025/03/25 15:22:42 by fmick            ###   ########.fr       */
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

int ft_handle_input_redir(t_re *redir)
{
    int fd;

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
