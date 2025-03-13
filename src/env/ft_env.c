/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:36:50 by fmick             #+#    #+#             */
/*   Updated: 2025/03/13 09:16:19 by Barmyh           ###   ########.fr       */
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
			tmp = ft_strjoin(temp->key, "=");
			tmp = ft_strjoin(tmp, temp->value);
			free(tmp);
		}
		temp = temp->next;
	}
}

t_env	*ft_add_env_node(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	if (!env->key || !env->value)
	{
		free(env->key);
		free(env->value);
		free(env);
		return NULL;
	}
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
		if (!temp)
			return (NULL);
		if (env == NULL)
			env = ft_add_env_node(temp[0], temp[1]);
		else
		{
			last = env;
			while (last->next)
				last = last->next;
			last->next = ft_add_env_node(temp[0], temp[1]);
		}
		i++;
		free (temp);
	}
	ft_env_display(env);
	return (env);
}

void	ft_sort_env(t_env *env)
{
	t_env	*lst;
	char	*tmpk;
	char	*tmpv;
	int swapped;

	if (!env)
		return;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->key, lst->next->key) > 0)
		{
			tmpk = lst->key;
			lst->key = lst->next->key;
			lst->next->key = tmpk;

			tmpv = lst->value;
			lst->value = lst->next->value;
			lst->next->value = tmpv;
		}
		lst = lst->next;
	}
}
}
/*

sort env, do when bored/have time TODO
	int		swapped;
	t_env	*ptr;
	t_env	*last = NULL;

	if (!env)
		return;
	
	do {
		swapped = 0;
		ptr = env;

		while (ptr->next != last)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0) // Compare keys
			{
				// Swap keys and values instead of nodes
				char *temp_key = ptr->key;
				char *temp_value = ptr->value;
				ptr->key = ptr->next->key;
				ptr->value = ptr->next->value;
				ptr->next->key = temp_key;
				ptr->next->value = temp_value;
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last = ptr;
	} while (swapped);*/
