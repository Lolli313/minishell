/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:37:20 by Barmyh            #+#    #+#             */
/*   Updated: 2025/03/13 07:44:08 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_find_key(t_env *env, char *key)
{
    t_env   *lst;

    lst = env;
    while (lst)
    {
        if (ft_strcmp(lst->key, key) == 0)
            return (lst->value);
        lst = lst->next;
    }
    return (NULL);
}

char    *ft_update_key(t_env *env, char *key, char *new_value)
{
    t_env   *lst;

    lst = env;
    while (lst)
    {
        if (ft_strcmp(lst->key, key) == 0)
        {
            free(lst->value);
            lst->value = ft_strdup(new_value);
            return NULL;
        }
        lst = lst->next;
    }
    return (NULL);
}

void    ft_unset_key(t_env *env, char *key)
{
    t_env *lst;
    t_env *prev;

    lst = env;
    prev = NULL;

    // Search for the node with the matching key
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
            return;
        }
        prev = lst;
        lst = lst->next;
    }
    // error if key not found
}