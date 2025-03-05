/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:02:33 by fmick             #+#    #+#             */
/*   Updated: 2025/03/05 13:21:23 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
// seaches env list to find env variable name (key) and returns a
// pointer to the correspinding value string - or NULL
char	*ft_get_env(const char *key, t_env *env)
{
	t_env	*lst;

	if (!key)
		return (NULL);
	lst = env;
	while (lst)
	{
		if (ft_strcmp(key, lst->key) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

// adds the var name to the env with a value
// if key exist value is change if overwrite is nonzero
// if overwrite is zero
int	ft_setenv(t_env *env, const char *key, const char *new_value, int overwrite)
{
    t_env   *lst;
    t_env   *new_node;

    if (!key || !new_value)
        return (-1);
    lst = env;
    while (lst)
    {
        if (ft_strcmp(key, lst->key) == 0 && overwrite > 0)
        {
            free(lst->value);
            lst->value = ft_strdup(new_value);
            return (0);
        }
        else if (!(ft_strcmp(key, lst->key) == 0) && overwrite == 0)
        {
            new_node = ft_add_env_node(key);
            if (new_node == NULL)
                return (-1);
            lst->next = new_node;
            return (0);
        }
        lst = lst->next;
    }
    return (0);
}
*/
