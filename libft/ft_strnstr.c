/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 08:52:14 by fmick             #+#    #+#             */
/*   Updated: 2024/10/25 15:20:58 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lil, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (lil[i] == '\0')
		return ((char *) big);
	while (big[i] && i < len)
	{
		j = 0;
		while (i + j < len && big[i + j] == lil[j] && big [i + j])
			j++;
		if (lil[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
