/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_externals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:36:43 by fmick             #+#    #+#             */
/*   Updated: 2025/03/27 07:00:09 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_external(t_mini *mini, char **args, char **envp)
{
	pid_t	cpid;

	mini->line->command[0] = check_external(mini->env, args[0]);
	if (!mini->line->command[0])
	{
		ft_putendl_fd("minishell: args[0]: command not found", 2);
		return ;
	}
	cpid = fork();
	if (cpid < 0)
		exit (1);
	if (cpid == 0)
	{
		if (execve(mini->line->command[0], args, envp) == -1)
			exit(1);
	}
	else // parent
		waitpid(cpid, NULL, 0);
}
/*

void	execute_external(t_env *env, char **args, char **envp)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (pid == 0) // Child process
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else // Parent process
	{
		waitpid(pid, &status, 0);
	}
}


void	execute_external(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0) // Child process
	{
		if (execve(args[0], args, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else // Parent process
	{
		waitpid(pid, &status, 0); // Wait for child to finish
	}
}

char	*find_command_in_path(char *cmd, char **envp)
{
	int		i;
	char	*path_env;
	char	*path;
	char	*full_cmd;
	char	**paths;

	// Find the PATH environment variable
	i = 0;
	while (envp[i] && strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path_env = envp[i] + 5; // Skip "PATH=" part

	// Split PATH into individual directories
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);

	// Try each path
	i = 0;
	while (paths[i])
	{
		full_cmd = ft_strjoin(paths[i], "/");
		full_cmd = ft_strjoin(full_cmd, cmd);
		if (access(full_cmd, X_OK) == 0) // Check if executable
			return (full_cmd);
		free(full_cmd);
		i++;
	}
	return (NULL);
}

void	execute_external(char **args, char **envp)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	// Check if command is an absolute path
	if (strchr(args[0], '/'))
		cmd_path = args[0];
	else
		cmd_path = find_command_in_path(args[0], envp);

	if (!cmd_path)
	{
		printf("Command not found: %s\n", args[0]);
		exit(1);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
		waitpid(pid, &status, 0);
}

*/
