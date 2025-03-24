/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:16 by fmick             #+#    #+#             */
/*   Updated: 2025/03/18 11:48:37 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int	ft_export(t_env **env, char *str)
{
	char	**temp;
	char	*key;
	char	*value;
	t_env	*last;

	temp = ft_split(str, '=');
	if (!temp || !temp[0])
		return (-1);
	key = temp[0];
	if (temp[1] != NULL)
		value = temp[1];
	else
		value = "";
	printf("Export key: %s\n", key);
	printf("Export value: %s\n", value);
	if (ft_env_exists(*env, key, value) == 0)
	{
		if (*env == NULL)
			*env = ft_add_env_node(key, value);
		else
		{
			last = *env;
			while (last->next)
				last = last->next;
			last->next = ft_add_env_node(key, value);
		}
	}
	free(temp[0]);
	free(temp[1]);
	free(temp);
	return (0);
}
