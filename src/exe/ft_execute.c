/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:53:53 by fmick             #+#    #+#             */
/*   Updated: 2025/05/14 11:35:17 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_hd(t_mini *mini)
{
	t_line	*line;
	t_re	*redir;

	line = mini->line;
	while (line)
	{
		redir = line->redirect;
		while (redir)
		{
			if (redir->type == LIMITER && redir->heredoc_fd >= 0)
			{
				ft_close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		line = line->next;
	}
}

static int	ft_hd(t_mini *mini, pid_t **pids)
{
	t_line	*current;

	current = mini->line;
	while (current)
	{
		if (current->redirect)
			ft_pipe_heredoc(mini, current);
		if (mini->skibidi == 1)
		{
			free(*pids);
			*pids = NULL;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	ft_execute_pipeline(t_mini *mini)
{
	t_line	*current;
	pid_t	*pids;
	int		i;

	i = 0;
	pids = malloc(sizeof(pid_t) * (mini->nbr_of_pipes + 1));
	if (ft_hd(mini, &pids))
		return ;
	current = mini->line;
	while (current)
	{
		if (current->next)
			ft_piped_cmd(mini, current, pids, i++);
		else
		{
			mini->pipe_out = -1;
			ft_fork_and_exe(mini, current, pids, i++);
		}
		current = current->next;
	}
	ft_supersafe_close(mini->pipe_in);
	ft_wait(mini, pids, i);
	free(pids);
}

void	ft_single_command(t_mini *mini)
{
	ft_execute_heredoc(mini);
	ft_handle_redirections(mini, mini->line);
	if (mini->skibidi == 1)
	{
		mini->exit_status = 1;
		return ;
	}
	if (ft_is_builtin(mini->line->command))
		ft_handle_builtin(mini, mini->line);
	else
		ft_handle_external(mini, mini->line->command);
}

void	ft_execute_command(t_mini *mini)
{
	if (mini->nbr_of_pipes == 0)
		ft_single_command(mini);
	else
		ft_execute_pipeline(mini);
	ft_close(mini->fd_in);
	ft_close(mini->fd_out);
	ft_close(mini->pipe_in);
	ft_close(mini->pipe_out);
	ft_close_hd(mini);
	mini->pipe_in = -1;
	mini->pipe_out = -1;
	ft_restore_std_fds(mini);
	mini->skibidi = 0;
	line_cleanup(mini);
}
