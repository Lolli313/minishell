/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:14 by fmick             #+#    #+#             */
/*   Updated: 2025/03/24 10:26:36 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	t_env	*lst;

	lst = env;
	if (!env)
		return (0);
	while (lst)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (0);
}
