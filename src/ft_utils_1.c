/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:40:10 by fmick             #+#    #+#             */
/*   Updated: 2025/03/29 14:56:34 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int ft_contains_type(t_token *tokens, t_type type)
{
    while (tokens)
    {
        if (tokens->type == type)  // Check if the token type is PIPE
            return 1;  // Found PIPE, return true
        tokens = tokens->next;
    }
    return 0;  // No PIPE found, return false
}

