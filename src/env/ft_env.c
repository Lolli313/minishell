/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:36:50 by fmick             #+#    #+#             */
/*   Updated: 2025/05/06 06:04:23 by Barmyh           ###   ########.fr       */
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

void	ft_env_display(t_env *env)
{
	t_env	*lst;
	char	*tmp;
	char	*joined;

	lst = env;
	while (lst)
	{
		if (lst->key && lst->value)
		{
			tmp = ft_strjoin(lst->key, "=");
			joined = ft_strjoin(tmp, lst->value);
			free(tmp);
			free(joined);
		}
		lst = lst->next;
	}
}

t_env	*ft_add_env_node(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (value != NULL)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	env->next = NULL;
	if (!env->key)
	{
		free(env->key);
		free(env->value);
		free(env);
		return (NULL);
	}
	return (env);
}

t_env	*ft_init_env(char **envp)
{
	char	**tmp;
	t_env	*env;
	int		i;
	t_env	*last;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		tmp = ft_split_env(envp[i]);
		if (env == NULL)
			env = ft_add_env_node(tmp[0], tmp[1]);
		else
		{
			last = env;
			while (last->next)
				last = last->next;
			last->next = ft_add_env_node(tmp[0], tmp[1]);
		}
		i++;
		free_matrix(tmp);
	}
	return (env);
}
