/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:00:42 by fmick             #+#    #+#             */
/*   Updated: 2024/10/25 15:48:04 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*temp_dest;
	char	*temp_src;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	temp_src = (char *) src;
	temp_dest = (char *) dest;
	i = 0;
	if (temp_dest > temp_src)
	{
		while (len-- > 0)
			temp_dest[len] = temp_src[len];
	}
	else
	{
		while (i < len)
		{
			temp_dest[i] = temp_src[i];
			i++;
		}
	}
	return (dest);
}
