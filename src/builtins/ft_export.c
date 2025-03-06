/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:16 by fmick             #+#    #+#             */
/*   Updated: 2025/03/06 08:14:21 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_add_node(char *key, char *value)
{
	t_env *env = malloc(sizeof(t_env));
	if (!env)
		return NULL;
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	return env;
}

int	ft_env_exists(t_env *env, char *key, char *value)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
			{
				if (ft_strcmp(lst->value, value) != 0)
				{
					free(lst->value);
					lst->value = ft_strdup(value);
					return (1);
				}
			return (0); // key found with same value
			}
		lst = lst->next;
	}
	return (0);
}

// locates the variable and eiter adds it to the end of the
// linked list of env variables or updates the value of an
// existing varuable /handles no arguments
int	ft_export(t_env *env, char *key, char *value)
{
	t_env	*lst;
	t_env	*new_node;

	lst = env;
	new_node = ft_add_node(key, value);
	if (!new_node)
		return -1;
	while (lst && lst->next)
		lst = lst->next;
	if (lst)
		lst->next = new_node;
	return (0);
}
