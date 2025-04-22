/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:36:50 by fmick             #+#    #+#             */
/*   Updated: 2025/04/22 19:25:32 by Barmyh           ###   ########.fr       */
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

char	**ft_split_env(char *str)
{
	char	**result;
	char	*equal_sign;
	size_t	key_len;

	result = malloc(sizeof(char *) * 3);
	if (!result)
		return (NULL);
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
	{
		result[0] = ft_strdup(str);
		result[1] = NULL;
	}
	else
	{
		key_len = equal_sign - str;
		result[0] = ft_substr(str, 0, key_len);
		result[1] = ft_strdup(equal_sign + 1);
	}
	result[2] = NULL;
	return (result);
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
	if (!env->key || !env->value)
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
	ft_shellvl(env);
	return (env);
}
