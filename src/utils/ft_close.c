/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:44:20 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/30 11:44:20 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_close(int fd)
{
	if (fd >= 0)
	{
		close(fd);
	}
}

void	ft_supersafe_close(int fd)
{
	if (fd >= 0)
	{
		ft_close(fd);
		fd = -1;
	}
}
