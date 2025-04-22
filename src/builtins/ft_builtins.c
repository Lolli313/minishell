/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:05:17 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/22 09:22:08 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char **av)
{
	if (!av || !av[0])
		return (0);
	if (ft_strncmp(av[0], "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(av[0], "cd", 2) == 0)
		return (1);
	if (ft_strncmp(av[0], "export", 6) == 0)
		return (1);
	if (ft_strncmp(av[0], "unset", 5) == 0)
		return (1);
	if (ft_strncmp(av[0], "env", 3) == 0)
		return (1);
	if (ft_strncmp(av[0], "echo", 4) == 0)
		return (1);
	if (ft_strncmp(av[0], "exit", 4) == 0)
		return (1);
	return (0);
}

void	ft_handle_builtin(t_mini *mini)
{
	t_env	*env;
	char	**cmd;

	cmd = mini->line->command;
	env = mini->env;
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		mini->exit_status = ft_pwd(env);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		mini->exit_status = ft_cd(cmd, env);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		mini->exit_status = ft_export(mini, cmd);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		mini->exit_status = ft_unset(mini, cmd);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		mini->exit_status = ft_env(env);
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
		mini->exit_status = ft_echo(cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		ft_exit(mini, cmd);
}
