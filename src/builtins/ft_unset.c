/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:22 by fmick             #+#    #+#             */
/*   Updated: 2025/04/10 14:59:32 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_mini *mini, char **av)
{
	int	i;
	int error;

	error = 0;
	i = 1;
	if (!av[i])
		return (0);
	while (av[i])
	{
		if (!export_validity(av[i]))
		{
			ft_putstr_fd("minishell: unset: ", STDERR);
			ft_putstr_fd(av[i], STDERR);
			ft_putendl_fd("': not a valid identifier", STDERR);
			error = 1;
		}
		else
		{
			ft_unset_key(mini->env, av[i]);
			ft_unset_key(mini->export_env, av[i]);
		}
		i++;
	}
	mini->exit_status = error;
	return (0);
}
