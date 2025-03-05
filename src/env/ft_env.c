/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:36:50 by fmick             #+#    #+#             */
/*   Updated: 2025/03/05 10:55:07 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints all environment variables stored in a linked list in the format
void	ft_env_display(t_env *env)
{
	t_env	*temp;
	char	*tmp;
	
	temp = env;
	while (temp)
	{
		if (temp->key && temp->value)
		{
			//ft_strjoin(temp->key, temp->key);
			tmp = ft_strjoin(temp->key, "=");
			tmp = ft_strjoin(tmp, temp->value);
			tmp = ft_strjoin(tmp, "\n");
		}
		printf("%s", tmp);
		temp = temp->next;
		free(tmp);
	}
}

t_env	*ft_add_env_node(char **array)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = array[0];
	env->value = array[1];
	env->next = NULL;
	return (env);
}

t_env	*ft_init_env(char **envp)
{
	char	**temp;
	t_env	*env;
	int		i;
	t_env	*last;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if (env == NULL)
			env = ft_add_env_node(temp);
		else
		{
			last = env;
			while (last->next)
				last = last->next;
			last->next = ft_add_env_node(temp);
		}
		i++;
		free (temp);
	}
	ft_env_display(env);
	return (env);
}
