/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:50 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/22 12:30:21 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*add_env_node(char **array)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = ft_strdup(array[0]);
	if (array[1] == NULL)
		env->value = ft_strdup("");
	else
		env->value = ft_strdup(array[1]);
	env->next = NULL;
	return (env);
}

void	print_env(t_env *env)
{
	t_env	*temp;
	
	temp = env;
	while (temp)
	{
		if (temp->key && temp->value)
			ft_printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

t_env	*init_env(char **envp)
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
			env = add_env_node(temp);
		else
		{
			last = env;
			while (last->next)
				last = last->next;
			last->next = add_env_node(temp);
		}
		i++;
		free_matrix(temp);
	}
//	print_env(env);
	return (env);
}
