/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:26:21 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/08 08:47:06 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	ft_handle_redirections(t_mini *mini)
{
	t_re	*redir;

	redir = mini->line->redirect;
	redir = mini->line->redirect;
	while (redir)
	{
		if (redir->type == INFILE)
			ft_handle_input_redir(mini, redir);
		else if (redir->type == OUTFILE || redir->type == APPEND_OUTFILE)
			ft_handle_output_redir(mini, redir);
		redir = redir->next;
	}
}

void	ft_handle_input_redir(t_mini *mini, t_re *redir)
{
	if (!redir->str)
	{
		perror("Redirection is NULL");
		exit(1);
	}
	mini->fd_in = open(redir->str, O_RDONLY);
	if (dup2(mini->fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(mini->fd_in);
		return ;
	}
	close(mini->fd_in);
}

void	ft_handle_output_redir(t_mini *mini, t_re *redir)
{
	if (redir->type == OUTFILE)
	{
		mini->fd_out = open(redir->str, O_CREAT | O_WRONLY | O_TRUNC, 0700);
		if (mini->fd_out == -1)
		{
			perror("Fail");
			exit(1);
		}
	}
	else if (redir->type == APPEND_OUTFILE)
	{
		mini->fd_out = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0700);
		if (mini->fd_out == -1)
		{
			perror("Fail");
			exit(1);
		}
	}
	if (dup2(mini->fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 output redirection\n");
		close(mini->fd_out);
		exit(1);
	}
	close(mini->fd_out);
}
