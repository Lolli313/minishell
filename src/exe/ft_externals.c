/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_externals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:36:43 by fmick             #+#    #+#             */
/*   Updated: 2025/04/10 15:13:42 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_external(t_env *env, char *command)
{
	char	**all_paths;
	char	*temp;
	char	*str;
	char	*str1;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
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

void	ft_handle_external(t_mini *mini, char **args)
{
	pid_t	cpid;
	char	*temp;
	char	**envp;

	envp = ft_env_to_array(mini->env);
	temp = check_external(mini->env, args[0]);
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
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(cpid, NULL, 0);
	}
	free_matrix(envp);
	free(temp);
}
