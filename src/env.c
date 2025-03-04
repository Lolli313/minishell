/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:50 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/04 15:22:40 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*add_env_node(char **array)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = array[0];
	env->value = array[1];
	env->next = NULL;
	return (env);
}

void	print_env(t_env *env)
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
		ft_printf("%s", tmp);
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
//	ft_printf("%s", envp[i]);
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
	}
	print_env(env);
	return (env);
}
