/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:40:10 by fmick             #+#    #+#             */
/*   Updated: 2025/02/28 13:38:35 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.c"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*dest;

	i = 0;
	while (s1[i])
		i++;
	len = i;

	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] == s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
