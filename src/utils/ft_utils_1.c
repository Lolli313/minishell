/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:40:10 by fmick             #+#    #+#             */
/*   Updated: 2025/04/22 15:24:44 by fmick            ###   ########.fr       */
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

int	ft_has_equal(t_mini *mini, char *str)
{
	char	**temp;
	char	*value;

	temp = ft_split_env(str);
	if (!temp[0] || !export_validity(temp[0]))
	{
		ft_putstr_fd("minishell: export: `", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd("': not a valid identifier\n", STDERR);
		free_matrix(temp);
		return (1);
	}
	else
	{
		if (temp[1])
			value = temp[1];
		else
			value = "";
		ft_add_env_export(mini, temp[0], value);
	}
	free_matrix(temp);
	return (0);
}

bool	ft_handle_token_error(t_mini *mini, t_token *current)
{
    if (current->type == PIPE && current->index == 0)
        return (ft_error_syntax(mini, current->str), false);
    else
        return (ft_error_syntax(mini, current->next->str), false);
}
