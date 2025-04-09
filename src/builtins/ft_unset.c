/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:22 by fmick             #+#    #+#             */
/*   Updated: 2025/04/09 06:48:57 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env variables
// handles "_" notcate the variable specified and then deletes it
// from the linked list of  being able to unset
int	ft_unset(t_mini *mini, char **av)
{
	int	i;

	i = 1;
	if (!av[i])
		return (0);
	while (av[i])
	{
		if (!export_validity(av[i]))
		{
			ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
			ft_putstr_fd(av[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
		else
		{
			ft_unset_key(mini->env, av[i]);
			ft_unset_key(mini->export_env, av[i]);
		}
		i++;
	}
	return (0);
}
