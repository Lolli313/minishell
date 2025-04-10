/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:26:21 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/10 12:36:53 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	ft_handle_redirections(t_mini *mini)
{
	t_re	*redir;
	int  	applied;

	applied = 0;
	redir = mini->line->redirect;
	while (redir)
	{
		if (redir->type == INFILE && applied == 0)
		{
			ft_handle_input_redir(mini, redir);
			ft_close(mini->fd_in);
			mini->fd_in = -1;
			applied = 1;
		}
		else if ((redir->type == OUTFILE || redir->type == APPEND_OUTFILE) && applied == 0)
		{
			ft_handle_output_redir(mini, redir);
			ft_close(mini->fd_out);
			mini->fd_out = -1;
			applied = 1;
		}
		redir = redir->next;
	}
}

void	ft_handle_input_redir(t_mini *mini, t_re *redir)
{
	ft_close(mini->fd_in);
	mini->fd_in = open(redir->str, O_RDONLY);
	if (mini->fd_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->str, 2);
		ft_putendl_fd(": No such file or directory", 2);
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
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(redir->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		return ;
	}
	ft_safe_dup2(mini->fd_out, STDOUT);
}
