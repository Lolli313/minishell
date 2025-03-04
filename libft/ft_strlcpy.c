/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:53:17 by fmick             #+#    #+#             */
/*   Updated: 2024/10/25 13:25:45 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < dsize)
		ft_memcpy(dest, src, srclen + 1);
	else if (dsize != 0)
	{
		ft_memcpy(dest, src, dsize - 1);
		dest[dsize - 1] = 0;
	}
	return (srclen);
}
