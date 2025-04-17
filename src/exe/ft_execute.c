/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:53:53 by fmick             #+#    #+#             */
/*   Updated: 2025/04/17 09:23:51 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_single_command(t_mini *mini)
{
	ft_execute_heredoc(mini);
	ft_handle_redirections(mini);
	if (ft_is_builtin(mini->line->command))
		ft_handle_builtin(mini);
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
