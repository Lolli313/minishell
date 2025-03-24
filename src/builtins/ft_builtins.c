/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:05:17 by Barmyh            #+#    #+#             */
/*   Updated: 2025/03/13 11:24:37 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle builtin commands (boolean expression, return true1 or false0)
int	ft_is_builtin(char **av)
{
	if (ft_strcmp(av[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(av[0], "cd") == 0)
		return (1);
	if (ft_strcmp(av[0], "export") == 0)
		return (1);
	if (ft_strcmp(av[0], "unset") == 0)
		return (1);
	if (ft_strcmp(av[0], "env") == 0)
		return (1);
	if (ft_strcmp(av[0], "echo") == 0)
		return (1);
	return 0;
}

// builtins execution
void	ft_handle_builtin(char **av, t_mini *mini)
{
	int     is_builtin;
    t_env   *env;

    env = mini->env;
	is_builtin = ft_is_builtin(av);
    if (is_builtin == 0)
    	return ; // TODO ERROR
    if (ft_strcmp(av[0], "pwd") == 0)
	    ft_pwd();
	else if (ft_strcmp(av[0], "cd") == 0)
	    ft_cd(av, env);
	else if (ft_strcmp(av[0], "export") == 0)
	    ft_export(&(mini->env), av[1]);
	else if (ft_strcmp(av[0], "unset") == 0)
	    ft_unset(mini, av);
	else if (ft_strcmp(av[0], "env") == 0)
	    ft_env(env);
	else if (ft_strcmp(av[0], "echo") == 0)
	    ft_echo(av);
}