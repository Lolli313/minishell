/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:22 by fmick             #+#    #+#             */
/*   Updated: 2025/03/13 07:45:48 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env variables
// handles "_" notcate the variable specified and then deletes it
// from the linked list of  being able to unset
int		ft_unset(t_mini *mini, char **av)
{
	t_env	*env;

	env = mini->env;
	if (av[1] == NULL)
		return 0;
	ft_unset_key(env, av[1]);
	return 0;
}
