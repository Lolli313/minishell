/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:37:20 by Barmyh            #+#    #+#             */
/*   Updated: 2025/05/06 07:42:38 by Barmyh           ###   ########.fr       */
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
			return (0);
		}
		lst = lst->next;
	}
	return (0);
}

static int	ft_count_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static void	ft_join_keyvalue(t_env *env, char **env_array, int i)
{
	char	*temp;

	env_array[i] = ft_strjoin(env->key, "=");
	temp = env_array[i];
	env_array[i] = ft_strjoin(temp, env->value);
	free(temp);
}

char	**ft_env_to_array(t_env *env)
{
	char	**env_array;
	t_env	*cur;
	int		i;

	cur = env;
	i = ft_count_env(cur);
	env_array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	cur = env;
	while (cur)
	{
		if (cur->key)
		{
			if (cur->value)
				ft_join_keyvalue(cur, env_array, i);
			else
				env_array[i] = ft_strjoin(cur->key, "=");
			i++;
		}
		cur = cur->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
