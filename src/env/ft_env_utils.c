/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:37:20 by Barmyh            #+#    #+#             */
/*   Updated: 2025/04/08 08:56:02 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(key, current->key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*ft_find_key(t_env *env, char *key)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

char	*ft_update_key(t_env *env, char *key, char *new_value)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			free(lst->value);
			lst->value = ft_strdup(new_value);
			return (NULL);
		}
		lst = lst->next;
	}
	return (NULL);
}

void	ft_unset_key(t_env *env, char *key)
{
	t_env	*lst;
	t_env	*prev;

	lst = env;
	prev = NULL;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			if (prev == NULL)
				env = lst->next;
			else
				prev->next = lst->next;
			free(lst->key);
			free(lst->value);
			free(lst);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
	perror("Key not found");
}

char	**ft_env_to_array(t_env *env)
{
	char	**env_array;
	char	*temp;
	t_env	*cur;
	int		count;
	int		i;

	count = 0;
	cur = env;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	cur = env;
	while (cur)
	{
		if (cur->key && cur->value)
		{
			env_array[i] = ft_strjoin(cur->key, "=");
			temp = env_array[i];
			env_array[i] = ft_strjoin(temp, cur->value);
			free(temp);
			if (!env_array[i])
			{
				perror("malloc u dimwit");
				while (i > 0)
					free(env_array[--i]);
				free(env_array);
				return (NULL);
			}
			i++;
		}
		cur = cur->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
