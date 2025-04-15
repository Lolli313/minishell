/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:14 by fmick             #+#    #+#             */
/*   Updated: 2025/04/15 11:46:34 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	t_env	*lst;

	lst = env;
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->value)
			ft_printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (0);
}
