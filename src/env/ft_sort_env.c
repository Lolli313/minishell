/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:07:28 by fmick             #+#    #+#             */
/*   Updated: 2025/03/05 09:20:05 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_value_len(t_env *env)
{
    int count;
    int i;

    while (env->value[i])
    {
        count++;
        i++;
    }
    return (count);
}

char    *ft_get_env_value(t_env *env, char *args)
{
    
}
