/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_externals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:36:43 by fmick             #+#    #+#             */
/*   Updated: 2025/04/23 14:57:41 by fmick            ###   ########.fr       */
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
	if (execve(temp, args, envp) == -1)
	{
		ft_error_msg(mini);
	}
	return (0);
}

static int	ft_exec_parent(t_mini *mini, pid_t cpid)
{
	g_skip = true;
	ft_wait(mini, &cpid, 1);
	g_skip = false;
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
	if (!temp)
	{
		ft_error_msg(mini);
		return (0);
	}
	envp = ft_env_to_array(mini->env);
	if (mini->skibidi == 1)
		return (mini->exit_status);
	cpid = fork();
	if (cpid < 0)
		exit(1);
	if (cpid == 0)
		ft_exec_child(mini, temp, args, envp);
	else
		ft_exec_parent(mini, cpid);
	free_matrix(envp);
	free(temp);
	return (0);
}
