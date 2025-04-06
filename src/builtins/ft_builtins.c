/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:05:17 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/06 11:14:19 by Barmyh           ###   ########.fr       */
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
	if (ft_strncmp(av[0], "exit", 5) == 0)
		return (1);
	return 0;
}

// builtins execution
void	ft_handle_builtin(t_mini *mini)
{
    t_env   *env;
	char **cmd;

	cmd = mini->line->command;
    env = mini->env;
	ft_handle_redirections(mini);
    if (ft_strncmp(cmd[0], "pwd", 3) == 0)
	    ft_pwd(env);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
	    ft_cd(cmd, env);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
	    ft_export(env, cmd);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
	    ft_unset(mini, cmd);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
	    ft_env(env);
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
	    ft_echo(cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
	    ft_exit(mini, cmd);
}
