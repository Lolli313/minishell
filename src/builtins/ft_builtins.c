/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:05:17 by Barmyh            #+#    #+#             */
/*   Updated: 2025/03/25 11:17:33 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle builtin commands (boolean expression, return true1 or false0)
int	ft_is_builtin(char **av)
{
	if (ft_strncmp(av[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(av[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(av[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(av[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(av[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(av[0], "echo", 5) == 0)
		return (1);
	return 0;
}

// builtins execution
void	ft_handle_builtin(char **av, t_mini *mini)
{
	int     is_builtin;
    t_env   *env;
	char **cmd;

	(void)av;
	cmd = mini->line->command;
    env = mini->env;
	is_builtin = ft_is_builtin(cmd);
    if (is_builtin == 0)
    	return ; // TODO ERROR
    if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	    ft_pwd(env);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
	{
		ft_printf (R "Entering CD\n" RESET);
	    ft_cd(cmd, env);
	}
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
	    ft_export(mini->env, cmd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
	    ft_unset(mini, cmd);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
	    ft_env(env);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
	    ft_echo(mini->line->command);
}
