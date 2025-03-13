/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:26:21 by Barmyh            #+#    #+#             */
/*   Updated: 2025/03/13 14:04:53 by Barmyh           ###   ########.fr       */
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

// type is redirection
int     ft_is_redir_type(t_token *token)
{
    if (!token)
        return (0);
    if (token->type == RE_INPUT)
        return (1);
    else if (token->type == RE_OUTPUT)
        return (1);
    else if (token->type == RE_APPEND)
        return (1);
    else if (token->type == HERE_DOC)
        return (1);
    return (0);
}

int     ft_redir_type(char *redir)
{
    int     i;

    i = 0;
    while (redir[i] && (redir[i] != '>' || redir[i] != '<'))
        i++;
    if (redir[i] == '>')
        return (RE_INPUT);
    else if (redir[i] == '<')
        return (RE_OUTPUT);
    else if (redir[i] == '>' && redir[i + 1] == '>')
        return (HERE_DOC);
    else if (redir[i] == '<' && redir[i + 1] == '<')
        return (RE_APPEND);
    return (0);
}

void     ft_redir_open_file(char *file, int type)
{
    int pipefd[2];

    if (type == HERE_DOC)
    {
        // pipefd[2] mumbojumbo
    }
    else if (type == RE_INPUT)
        open(file, O_RDONLY); //readonly
    else if (type == RE_OUTPUT)
        open(file, O_WRONLY); //writeonly
    else if (type == RE_APPEND)
        open(file, O_WRONLY, O_APPEND);
}

void    ft_redirection(t_token *token, t_mini *mini)
{

}