/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:22 by fmick             #+#    #+#             */
/*   Updated: 2025/03/25 09:49:42 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env variables
// handles "_" notcate the variable specified and then deletes it
// from the linked list of  being able to unset
int		ft_unset(t_mini *mini, char **av)
{
	t_env	*env;
	int		i;

	i = 1;
	env = mini->env;
	if (av[i] == NULL)
		return 0;
	while (av[i])
	{
		ft_unset_key(env, av[i]);
		i++;
	}
	return 0;
}
