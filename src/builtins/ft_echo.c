/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:12 by fmick             #+#    #+#             */
/*   Updated: 2025/04/08 08:45:11 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_nbr_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_echo(char **args)
{
	int	nflag;
	int	i;

	nflag = 0;
	i = 1;
	if (ft_nbr_of_args(args) > 1)
	{
		while (args[i] && echo_validity(args[i]) == true)
		{
			nflag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1])
			{
				write(1, " ", 1);
			}
			i++;
		}
	}
	if (nflag == 0)
		write(1, "\n", 1);
	return (0);
}
