/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:01:23 by fmick             #+#    #+#             */
/*   Updated: 2025/03/05 09:51:19 by fmick            ###   ########.fr       */
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

void	ft_handle_builtin(char **av)
{
	
	if (ft_strcmp(av[0], "echo") == 0)
		ft_echo(av);
//	if (ft_strcmp(av[0], "exit") == 0)
//		mini->exit_flag = 0;
/*
		if (ft_strcmp(av[0], "pwd") == 0)
			ft_pwd();
		if (ft_strcmp(av[0], "cd") == 0)
			ft_cd();
		if (ft_strcmp(av[0], "export") == 0)
			ft_export(); 
		if (ft_strcmp(av[0], "unset") == 0)
			ft_unset();
		if (ft_strcmp(av[0], "env") == 0)
			ft_env();
		if (ft_strcmp(av[0], "echo") == 0)
			ft_echo();
*/
}


/*
// function to execute (...) commands
// EXECUTABLES != builtins
void	ft_execute_command(char **av)
{
	if(ft_handle_builtin(av)) // if no matching command found
	{
		// ex. l: command not found
		return ;
	}

	if(ft_handle_external(av))
	{
		pid_t	pid;

		pid = fork();
		if (pid < 0)
			return ; // fork failed
		else if (pid == 0)
		{
			// execvp(av[0], av);
			// exit(EXIT_FAILURE);
		}
		else
			// waitpid(pid, NULL, 0??)
	}
}
*/
