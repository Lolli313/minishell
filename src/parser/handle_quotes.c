/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:54:49 by aakerblo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/10 14:53:04 by Barmyh           ###   ########.fr       */
=======
/*   Updated: 2025/04/10 16:20:51 by aakerblo         ###   ########.fr       */
>>>>>>> f3caab318bddd14ac2e0ab7fd9079fe3dcdb2e60
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*if_empty_quote(char *before, char *sub, int len, char *org)
{
	char	*result;
	char	*temp;
	char	*temp1;

	temp = ft_substr(sub, len + 1, ft_strlen(org));
	temp1 = ft_strdup(before);
	result = ft_strjoin(temp1, temp);
	free_many(temp, before, org, temp1);
	return (result);
}

char	*handle_single_quote(char *org, char *sub, int *pos)
{
	char	*result;
	char	*temp;
	char	*temp1;
	int		len;

	len = 1;
	temp = ft_substr(org, 0, *pos);
	if (org[*pos + 1] == '\'')
		return (if_empty_quote(temp, sub, len, org));
	while (sub[len])
	{
		if (sub[len] == '\'')
			break ;
		len++;
	}
	temp1 = ft_substr(org, *pos + 1, len - 1);
	result = ft_strjoin(temp, temp1);
	free_many(temp, temp1, 0, 0);
	temp = ft_substr(sub, len + 1, ft_strlen(org));
	temp1 = ft_strjoin(result, temp);
	free_many(temp, result, org, 0);
	*pos += len - 1;
	return (temp1);
}

char	*check_double_quote_variable(t_mini *mini, char *org, int *pos)
{
	char	*temp2;
	int		len;

	len = 0;
	temp2 = org;
	(void)pos;
	while (temp2[len])
	{
		if (temp2[len] == '$')
			temp2 = handle_dollar_sign(mini, temp2, temp2 + len, &len);
		else
			len++;
	}
	return (temp2);
}

char	*handle_double_quote(t_mini *mini, char *org, char *sub, int *pos)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		len;

	len = 1;
	temp1 = ft_substr(org, 0, *pos);
	if (sub[1] == '\"')
		return (if_empty_quote(temp1, sub, len, org));
	while (sub[len])
	{
		if (sub[len] == '\"')
			break ;
		len++;
	}
	temp2 = ft_substr(org, *pos + 1, len - 1);
	temp2 = check_double_quote_variable(mini, temp2, &len);
	temp3 = ft_strjoin(temp1, temp2);
	*pos += ft_strlen(temp2);
	free_many(temp1, temp2, 0, 0);
	temp1 = ft_substr(sub, len + 1, ft_strlen(org));
	temp2 = ft_strjoin(temp3, temp1);
	free_many(temp1, temp3, org, 0);
	return (temp2);
}
