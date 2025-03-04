/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:22:02 by fmick             #+#    #+#             */
/*   Updated: 2024/10/24 09:44:52 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t len)
{
	ft_memset(s, 0, len);
}
/*
void	ft_bzero(void *s, size_t len)
{
	char	*temp_s;

	temp_s = (char *) s;
	while (n > 0)
	{
		*temp_s = 0
		temp_s++;
		len--;
	}
}
*/
