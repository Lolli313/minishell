/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_externals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:36:43 by fmick             #+#    #+#             */
/*   Updated: 2025/05/06 12:02:27 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_external(t_mini *mini, t_env *env, char *command)
{
	char	**all_paths;
	char	*temp;
	char	*str;
	char	*str1;
	int		i;

	(void)mini;
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	temp = ft_getenv(env, "PATH");
	all_paths = ft_split(temp, ':');
	free(temp);
	i = 0;
	while (all_paths[i])
	{
		str = ft_strjoin(all_paths[i], "/");
		str1 = ft_strjoin(str, command);
		free(str);
		if (access(str1, X_OK) == 0)
			return (free_matrix(all_paths), str1);
		free(str1);
		i++;
	}
	free_matrix(all_paths);
	return (NULL);
}

static int	ft_exec_child(t_mini *mini, char *temp, char **args, char **envp)
{
	handle_function_signals();
	if (execve(temp, args, envp) == -1)
	{
		ft_error_msg(mini, args[0]);
	}
	return (mini->exit_status);
}

int	ft_wait2(t_mini *mini, pid_t *pids, int i)
{
	int	status;
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &status, 0);
        if (j == i - 1)
		{
            if (WIFEXITED(status))
                mini->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
            {
                if (WTERMSIG(status) == SIGQUIT)
                {
                    if (mini->nbr_of_pipes == 0)
                        ft_putstr_fd("Quit (core dumped)\n", 2);
                    mini->exit_status = 131;
                }
                else if (WTERMSIG(status) == SIGINT)
                    mini->exit_status = 130;
                else
                    mini->exit_status = 128 + WTERMSIG(status);
            }
        }
		j++;
	}
	return (mini->exit_status);
}

static int	ft_exec_parent(t_mini *mini, pid_t cpid)
{
	ft_wait2(mini, &cpid, 1);
	return (0);
}

int	ft_handle_external(t_mini *mini, char **args)
{
	pid_t	cpid;
	char	*temp;
	char	**envp;

	if (!args)
		return (0);
	temp = check_external(mini, mini->env, args[0]);
	if (!temp || ft_strlen(args[0]) == 0)
	{
		ft_error_msg(mini, args[0]);
		free(temp);
		return (0);
	}
	envp = ft_env_to_array(mini->env);
	cpid = fork();
	if (cpid < 0)
		exit(1);
	if (cpid == 0)
		ft_exec_child(mini, temp, args, envp);
	else
		ft_exec_parent(mini, cpid);
	handle_signals();
	free_matrix(envp);
	free(temp);
	return (0);
}
