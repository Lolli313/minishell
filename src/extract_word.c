/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:34:42 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/28 17:37:20 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_extract(t_extract *extract, int pos)
{
	extract->start = pos;
	extract->len = 0;
	extract->in_quotes = false;
	extract->quote_char = '\0';
}

char	*check_unclosed_quote(t_extract *extract, int *pos, char *input)
{
	if (extract->in_quotes)
		return (ft_printf("Error: Unclosed quote detected\n"), NULL);
	*pos = extract->start + extract->len;
	return (ft_substr(input, extract->start, extract->len));
}

char	*extract_word(t_extract *extract, char *input, int *pos)
{
	init_extract(extract, *pos);
	while (input[extract->start + extract->len])
	{
		if ((input[extract->start + extract->len] == '\''
				|| input[extract->start + extract->len] == '\"')
			&& (!extract->in_quotes || input[extract->start
					+ extract->len] == extract->quote_char))
		{
			if (!extract->in_quotes)
			{
				extract->in_quotes = true;
				extract->quote_char = input[extract->start + extract->len];
			}
			else
			{
				extract->in_quotes = false;
				extract->quote_char = '\0';
			}
		}
		if (!extract->in_quotes && (input[extract->start + extract->len] == ' '
				|| is_operator_char(input[extract->start + extract->len])))
			break ;
		extract->len++;
	}
	return (check_unclosed_quote(extract, pos, input));
}
