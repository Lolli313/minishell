/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:53:53 by fmick             #+#    #+#             */
/*   Updated: 2025/04/22 16:18:40 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_hd(t_mini *mini)
{
	t_line	*current;

	current = mini->line;
	while (current)
	{
		if (current->redirect)
			ft_pipe_heredoc(mini, current);
		current = current->next;
	}
}

void	ft_execute_pipeline(t_mini *mini)
{
	t_line	*current;
	pid_t	*pids;
	int		i;

	i = 0;
	pids = malloc(sizeof(pid_t) * (mini->nbr_of_pipes + 1));
	ft_hd(mini);
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
	if (ft_is_builtin(mini->line->command))
		ft_handle_builtin(mini, mini->line);
	else
		ft_handle_external(mini, mini->line->command);
	if (mini->skibidi == 1)
		mini->exit_status = 1;
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
	mini->pipe_in = -1;
	mini->pipe_out = -1;
	ft_restore_std_fds(mini);
}
