/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:40:10 by fmick             #+#    #+#             */
/*   Updated: 2025/05/07 11:06:06 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	update_or_add_env(t_env **list, char *key, char *value)
{
	t_env	*curr;
	t_env	*new_node;

	curr = *list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	new_node = ft_add_env_node(key, value);
	if (*list == NULL)
		*list = new_node;
	else
	{
		curr = *list;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
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

bool	ft_handle_token_error(t_mini *mini, t_token *current)
{
	if (current->type == PIPE && current->index == 0)
		return (ft_error_syntax(mini, current->str), false);
	else
		return (ft_error_syntax(mini, current->next->str), false);
}
