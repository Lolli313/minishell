/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_externals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:36:43 by fmick             #+#    #+#             */
/*   Updated: 2025/03/31 14:33:18 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_absolute_command(char *command)
{
	if (access(command, X_OK) == 0)
		return (command);
	else
		return (NULL);
}

char	*check_external(t_env *env, char *command)
{
	char	**all_paths;
	char	*temp;
	char	*str;
	char	*str1;
	int		i;
	
	if (ft_strncmp(command, "/", 1) == 0)
		return (check_absolute_command(command));
	temp = ft_getenv(env, "PATH");
	if (ft_strncmp(temp, "PATH=", 5) == 0)
		temp += 5;
	all_paths = ft_split(temp + 5, ':');
	free(temp);
	i = 0;
	while (all_paths[i])
	{
		str = ft_strjoin(all_paths[i], "/");
		str1 = ft_strjoin(str, command);
		free(str);
		if (access(str1, X_OK) == 0)
		{
			free_matrix(all_paths);
			return (str1);
		}
		free(str1);
		i++;
	}
	free_matrix(all_paths);
	return (NULL);
}

void	ft_handle_external(t_mini *mini, char **args, char **envp)
{
	pid_t	cpid;
	char	*temp;
	
	temp = check_external(mini->env, args[0]);
	if (!temp)
	{
		ft_putendl_fd("minishell: args[0]: command not found", 2);
		return ;
	}
    // mini->line->command[0] = temp;
	cpid = fork();
    if (cpid < 0)
    {
        perror("fork");
        free(temp);
        exit(1);
    }
	if (cpid == 0)
	{
		ft_handle_redirections(mini);
		if (execve(temp, args, envp) == -1)
		{
			perror("execvp error");
			free(temp);
			exit(EXIT_FAILURE);
		}
	}
	else // parent
	{
        waitpid(cpid, NULL, 0);
	}
	free(temp);
}
