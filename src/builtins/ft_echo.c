/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:12 by fmick             #+#    #+#             */
/*   Updated: 2025/03/06 13:45:47 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_nbr_of_av(char **av)
{
	int	i;

	i = 0;
	while(av[i])
		i++;
	return (i);
}
// ft_echo(["echo", "hello", "world"]);
// Expected output: "hello world"
// handles option -n to print the arguments
// without a \n at the end
int	ft_echo(char **av)
{
	int	nflag;
	int i;

	nflag = 0;
	i = 1;

	if (ft_nbr_of_av(av) > 1)
	{
		while (av[i] && ft_strcmp(av[i], "-n") == 0)
		{
			nflag = 1;
			i++;
		}
		while (av[i])
		{
			printf ("entering loop\n");
			ft_putstr_fd(av[i], 1);
			printf ("%s\n", av[i]);
			if (av[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	printf("nflag = %d\n", nflag);
	if (nflag == 0)
		write (1, "\n", 1);
	return (0);
}
