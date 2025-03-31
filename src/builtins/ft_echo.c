/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:12 by fmick             #+#    #+#             */
/*   Updated: 2025/03/30 06:47:06 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_nbr_of_args(char **args)
{
	int	i;

	i = 0;
	while(args[i])
		i++;
	return (i);
}
// ft_echo(["echo", "hello", "world"]);
// Expected output: "hello world"
// handles option -n to print the arguments
// without a \n at the end
int	ft_echo(char **args)
{
	int	nflag;
	int i;

	nflag = 0;
	i = 1;
	if (ft_nbr_of_args(args) > 1)
	{
		while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
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
		write (1, "\n", 1);
	return (0);
}
