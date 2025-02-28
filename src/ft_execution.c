/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:01:23 by fmick             #+#    #+#             */
/*   Updated: 2025/02/28 10:25:15 by fmick            ###   ########.fr       */
/*                                                                            */
/* ****************************************************************************/

#include "minishell.h"

// handle builtin commands (cd, exit, ...)
// return 0 if not returns 1 if built in
int	ft_handle_builtin(char **av)
{
	// for exit
	if (strcmp(av[0]), "exit" == 0)
	{
		printf("exit\n");
		exit(EXIT_SUCCES);
	}

	// for pwd
	if (strcmp(av[0]), "pwd" == 0)
	{
		// print working directory
	}

	// cd
	if (strcmp(av[0]), "cd" == 0)
	{
		// change directory
		// different cd
		// cd 
		// cd .. (move up one lvl)
		// cd - (return to previous directory)
		// cd ~ (goes to home directory)
	}

	// export
	if (strcmp(av[0]), "export" == 0)
	{
		// export (variable=value)
		// ex : export PATH=$PATH:/new/directory
	}

	// unset
	if (strcmp(av[0]), "unset" == 0)
	{
		// unset variable
		// removes shell variables or functions
		// ex: unset MY_VAR
	}

	// env
	if (strcmp(av[0]), "env" == 0)
	{
		// display or set environment variables
		// ex: env (variable=value) or env
	}

	// echo
	if (strcmp(av[0]), "echo" == 0)
	{
		// print text to terminal
		// ex: echo (string)
	}
	return 0;
}

// handle external commands (ls, grep, ...) return 0 or 1 if false or true
int	ft_handle_external(char **av)
{
	return 0;
}

// function to execute (...) commands
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
