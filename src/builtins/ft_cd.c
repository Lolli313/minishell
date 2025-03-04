/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:06 by fmick             #+#    #+#             */
/*   Updated: 2025/03/04 09:25:27 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **av)
{
	t_mini	*mini;

	if (av[1] == NULL || ft_strcmp(av[1], "~") == 0)
	{
      // TODO NEED TO WORK WITH T_ENV //
	}
	else if (ft_strcmp(av[1], "..") == 0)
	{
		//	chdir(???) //
		// up one level until max
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{

	}
		
	// cd /nonexistant: No such file or directory
	// cd /file: Not a directory
}
