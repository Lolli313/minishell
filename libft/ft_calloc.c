/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:37:55 by fmick             #+#    #+#             */
/*   Updated: 2024/10/29 11:34:56 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;
	size_t			total;

	total = size * count;
	if (total != 0 && total / count != size)
		return (NULL);
	temp = malloc(total);
	if (!temp)
		return (NULL);
	ft_memset(temp, 0, total);
	return (temp);
}
