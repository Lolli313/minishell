/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:16 by fmick             #+#    #+#             */
/*   Updated: 2025/03/26 11:58:40 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// change the value of existing key
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
int	ft_export(t_env *env, char **str)
{
	char 	**temp;
	t_env	*last;
	int		i;

	i = 1;
	while (str[i])
	{
		temp = ft_split(str[i], '=');
		if (export_validity(temp[0]))
		{
			if (ft_env_exists(env, temp[0], temp[1]) == 0)
			{
				if (env == NULL)
					env = ft_add_env_node(temp[0], temp[1]);
				else
				{
					last = env;
					while (last->next)
						last = last->next;
					last->next = ft_add_env_node(temp[0], temp[1]);
				}
			}
		}
		int j = 0;
		while (temp[j])
			free(temp[j++]);
		free(temp);
		i++;
	}
	return (0);
}
