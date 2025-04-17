/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:26:21 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/17 08:43:18 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_redirections(t_mini *mini)
{
	t_re	*redir;

	redir = mini->line->redirect;
	while (redir)
	{
		if (mini->skibidi == 1)
			break ;
		if (redir->type == INFILE)
			ft_handle_input_redir(mini, redir);
		else if ((redir->type == OUTFILE || redir->type == APPEND_OUTFILE))
			ft_handle_output_redir(mini, redir);
		redir = redir->next;
	}
}

void	ft_handle_input_redir(t_mini *mini, t_re *redir)
{
	ft_close(mini->fd_in);
	mini->fd_in = open(redir->str, O_RDONLY);
	if (mini->fd_in == -1)
	{
		if (access(redir->str, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(redir->str, STDERR);
			ft_putendl_fd(": No such file or directory", STDERR);
		}
		else
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(redir->str, STDERR);
			ft_putendl_fd(": Permission denied", STDERR);
		}
		mini->exit_status = 1;
		mini->skibidi = 1;
		return ;
	}
	ft_safe_dup2(mini->fd_in, STDIN);
}

void	ft_handle_output_redir(t_mini *mini, t_re *redir)
{
	ft_close(mini->fd_out);
	if (redir->type == OUTFILE)
		mini->fd_out = open(redir->str, O_CREAT | O_WRONLY | O_TRUNC, 00700);
	else if (redir->type == APPEND_OUTFILE)
		mini->fd_out = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 00700);
	if (mini->fd_out == -1)
	{
		if (access(redir->str, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(redir->str, STDERR);
			ft_putendl_fd(": No such file or directory", STDERR);
		}
		else
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(redir->str, STDERR);
			ft_putendl_fd(": Permission denied", STDERR);
		}
		mini->exit_status = 1;
		mini->skibidi = 1;
		return ;
	}
	ft_safe_dup2(mini->fd_out, STDOUT);
}
