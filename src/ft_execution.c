/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:01:23 by fmick             #+#    #+#             */
/*   Updated: 2025/03/13 06:07:01 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// count size of env
static int		ft_env_size(t_env *env)
{
	t_env	*lst;
	int	count;

	count = 0;
	lst = env;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return count;
}

// combine key + value;
static char	**ft_combine_keyvalue(t_mini *mini)
{
	char	**envp;
	int		count;
	int		len;
	int		i;
	t_env	*env_lst;

	count = ft_env_size(mini->env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return 0;
	env_lst = mini->env;
	i = 0;
	while (env_lst)
	{
		len = ft_strlen(env_lst->key) + ft_strlen(env_lst->value) + 2; // = + \0
		envp[i] = malloc(len);

		ft_strlcpy(envp[i], env_lst->key, ft_strlen(env_lst->key) + 1);
		ft_strlcat(envp[i], "=", len);
		ft_strlcat(envp[i], env_lst->value, len);
		env_lst = env_lst->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
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
	int		pipefd[(ac - 1)][2]; // 0 read 1 write | array to hold pair of fds
	int	i;
	char **envp;

	mini->stdin = STDIN_FILENO;
	mini->stdout = STDOUT_FILENO;
	i = 0;
	cpid = (pid_t *)malloc(sizeof(pid_t) * (ac - 1));
	if (!cpid)
		return ;
	while (i < (ac - 1))
	{
		// handle error pipe failed TODO
		cpid[i] = fork();
		if (cpid[i] < 0)
		{
			printf(R "fork failed (ft_handle_external)" RESET);
			free(cpid);
			return ;
		}
		else if (cpid[i] == 0) // if it's child process
		{
			if (i == 0) // if first pipe
				dup2(pipefd[i][1], mini->stdout);
			else if (i == ac - 2) // if last pipe
				dup2(pipefd[i - 1][0], mini->stdin);
			else // if pipes in the middle
			{
				dup2(pipefd[i - 1][0], mini->stdin);
				dup2(pipefd[i][1], mini->stdout);
			}
			close(pipefd[i][0]);
			close(pipefd[i][1]);
		}
		envp = ft_combine_keyvalue(mini);
		if (execve(av[i + 1], &av[i + 1], envp) == -1)
		{
			printf(R "Error handle external\n" RESET);
			exit(1);
		}
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;

	}
		while (i < ac - 1) // wait for childprocesses to be done
		{
		waitpid(cpid[i], NULL, 0); // exit_code = TODO
		i++;
		}
	free(cpid);
}

// check execve (pathname, argv, envp)
// check pipex -> arttu

/*

void	redir (char *cmd, char **env, int fdin)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		if (fdin == STDIN)
			exit(1);
		else
			exec(cmd, env);
	}
}
*/
