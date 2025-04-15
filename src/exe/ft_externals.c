/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_externals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:36:43 by fmick             #+#    #+#             */
/*   Updated: 2025/04/15 14:04:02 by fmick            ###   ########.fr       */
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
	ft_error_msg(mini);
	free_matrix(all_paths);
	return (NULL);
}

int	ft_handle_external(t_mini *mini, char **args)
{
	pid_t	cpid;
	char	*temp;
	char	**envp;
	int 	status;

	envp = ft_env_to_array(mini->env);
	temp = check_external(mini, mini->env, mini->line->command[0]);
	if (mini->skibidi == 1)
		return (mini->exit_status);
	cpid = fork();
	if (cpid < 0)
	{
		perror("fork");
		free_matrix(envp);
		free(temp);
		exit(1);
	}
	if (cpid == 0)
	{
		if (execve(temp, args, envp) == -1)
		{
			free_matrix(envp);
			free(temp);
			exit(127);
		}
	}
	else
		waitpid(cpid, &status, 0);
	free_matrix(envp);
	free(temp);
	return (0);
}
