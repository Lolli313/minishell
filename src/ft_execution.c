/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:01:23 by fmick             #+#    #+#             */
/*   Updated: 2025/03/07 13:20:11 by fmick            ###   ########.fr       */
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

void	ft_handle_builtin(char **av, t_mini *mini)
{
	
	if (ft_strcmp(av[0], "echo") == 0)
		ft_echo(av);
	if (ft_strcmp(av[0], "export") == 0)
		ft_export(mini->env, mini->env->key, mini->env->value); 
	if (ft_strcmp(av[0], "env") == 0)
		ft_env(mini->env);
	if (ft_strcmp(av[0], "pwd") == 0)
		ft_pwd();
/*	if (ft_strcmp(av[0], "cd") == 0)
		ft_cd();
	if (ft_strcmp(av[0], "unset") == 0)
		ft_unset();
	if (ft_strcmp(av[0], "echo") == 0)
		ft_echo(); */
}

/*
smth    | smth1    | smth2
  |           |          |
  v           v          v
stdout -> pipefd[1] -> pipefd[0] -> stdin (smth1)
stdout -> pipefd2[1] -> stdin (smth2)
---------------------------------------------
You create a new child process for each pipe in the command line
Yes, each command in the pipeline gets its own child process.
Each child process has its own file descriptors and executes the command independently.
dup2 is used to set up input/output redirection, connecting
the output of one process to the input of the next.
*/
// create pipes based on number of commands
// fork child processes to execute each command
// set up dup2 to connect pipes correctly
// close unused pipes in each process
// wait for all child processes to finish
void	ft_handle_external(int ac, char **av, t_mini *mini)
{
	pid_t	*cpid; // childpid
	int		pipefd[2 * (ac - 1)][2]; // 0 read 1 write | array to hold pair of fds
	int	i;

	(void)av;
	(void)mini;
	i = 0;
	cpid = (pid_t *)malloc(sizeof(pid_t) * (ac - 1));
	if (!cpid)
		return ;
	while (i < (ac - 1))
	{
		cpid[i] = fork();
		if (cpid < 0)
		{
			printf(R "fork failed (ft_handle_external)" RESET);
			return ;
		}
		else if (cpid[i] == 0) // if it's child process
		{
			if (i == 0) // if first pipe
				dup2(pipefd[i][1], STDOUT_FILENO);
			else if (i == ac - 2) // if last pipe
				dup2(pipefd[i - 1][0], STDIN_FILENO);
			else // if pipes in the middle
			{
				dup2(pipefd[i - 1][0], STDIN_FILENO);
				dup2(pipefd[i][1], STDOUT_FILENO);
			}
		//	execve();
		}
		while (i < ac - 1)
			{
				close(pipefd[i][0]);
				close(pipefd[i][1]);
			}
		while (i < ac - 1) // wait for childprocesses to be done
			waitpid(cpid[i], NULL, 0);
		i++;
	}
	free(cpid);
}
/*

int	execute_first_command(char **args, char **envp, int pipefd[2], int fd)
{
	pid_t	pid;
	char	*temp;
 
	temp = valid_command(args[0], envp);
	if (temp == 0)
		return (pipe_first_command_nonexistent(args[0]));
	free(args[0]);
	args[0] = temp;
	pid = fork();
	if (pid == -1)
		pipe_print_error_code("Error forking");
	else if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(fd, 0) == -1 || dup2(pipefd[1], 1) == -1)
			pipe_print_error_code("Error duplicating file descriptor");
		close(pipefd[1]);
		if (execve(args[0], args, envp) == -1)
		{
			free_variable(args);
			pipe_print_error_code("Error executing command");
		}
	}
	return (pid);
}
 
int	execute_second_command(char **args, char **envp, int pipefd[2], int fd)
{
	pid_t	pid;
	char	*temp;
 
	temp = valid_command(args[0], envp);
	if (temp == 0)
		pipe_second_command_nonexistent(args[0], args);
	free(args[0]);
	args[0] = temp;
	pid = fork();
	if (pid == -1)
		pipe_print_error_code("Error forking");
	else if (pid == 0)
	{
		close(pipefd[1]);
		if (dup2(fd, 1) == -1 || dup2(pipefd[0], 0) == -1)
			pipe_print_error_code("Error duplicating file descriptor");
		close(pipefd[0]);
		if (execve(args[0], args, envp) == -1)
		{
			free_variable(args);
			pipe_print_error_code("Error executing command");
		}
	}
	return (pid);
}
 
int	first_command_setup(char *argv, char **envp, int pipefd[2], int fd)
{
	char	**args;
	int		pid;
 
	pid = 0;
	if (ft_strlen(argv) == 0)
		return (0);
	args = ft_split(argv, ' ');
	if (fd > -1)
		pid = execute_first_command(args, envp, pipefd, fd);
	close(fd);
	free_variable(args);
	return (pid);
}
 
int	second_command_setup(char *argv, char **envp, int pipefd[2], int fd)
{
	char	**args;
	int		pid;
 
	pid = 0;
	if (ft_strlen(argv) == 0)
		return (0);
	args = ft_split(argv, ' ');
	if (fd > -1)
		pid = execute_second_command(args, envp, pipefd, fd);
	close(fd);
	free_variable(args);
	return (pid);
}

void	valid_input(int argc)
{
	if (argc >= 6)
		pipe_print_error("Error: too many arguments\n");
	else if (argc <= 4)
		pipe_print_error("Error: too few arguments\n");
}
 
void	free_variable(char **args)
{
	int	i;
 
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}
 
char	*valid_command_check(char **all_paths, char *command)
{
	char	*str;
	char	*temp;
	int		i;
 
	i = 0;
	while (all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		str = ft_strjoin(temp, command);
		free(temp);
		if (access(str, X_OK) == 0)
			return (str);
		free(str);
		i++;
	}
	return (0);
}
 
char	*valid_command(char *command, char **envp)
{
	char	**all_paths;
	char	*path;
	char	*temp;
 
	if (strncmp(command, "/", 1) == 0)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
	}
	temp = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			temp = *envp;
			break ;
		}
		envp++;
	}
	if (temp == NULL)
		pipe_print_error("Error: PATH environment variable missing");
	all_paths = ft_split(temp + 5, ':');
	path = valid_command_check(all_paths, command);
	free_variable(all_paths);
	return (path);
}

int    main(int argc, char **argv, char **envp)
{
    int        pipefd[2];
    int        status;
    t_file    file;
    int        f_pid;
    int        s_pid;
 
    valid_input(argc);
    file.infile = open(argv[1], O_RDONLY);
    if (file.infile == -1)
        perror(argv[1]);
    if (pipe(pipefd) == -1)
        pipe_print_error_code("Error pipeing");
    f_pid = first_command_setup(argv[2], envp, pipefd, file.infile);
    file.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
    s_pid = second_command_setup(argv[3], envp, pipefd, file.outfile);
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(f_pid, &status, 0);
    waitpid(s_pid, &status, 0);
    if (file.outfile == -1)
        pipe_print_error_code(argv[4]);
    if ((status & 0x7F) == 0)
        exit((status >> 8) & 0xFF);
    return (0);
}
*/
