/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:00:08 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/08 09:13:06 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_dollar_get_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
			break ;
	}
	return (i);
}

char	*handle_dollar_sign_single(t_env *env, char *b4, char *org, int *pos)
{
	char	*result;
	char	*temp;
	char	*temp1;

	if (org[*pos + 1] == '$')
	{
		temp = ft_getenv(env, "SYSTEMD_EXEC_PID");
		temp1 = ft_strjoin(b4, temp);
		free(temp);
		temp = ft_substr(org, *pos + 2, ft_strlen(org));
		*pos += ft_strlen(temp1);
		result = ft_strjoin(temp1, temp);
		free(temp1);
		free(temp);
	}
	else
		result = ft_strjoin(b4, org + *pos + 1);
	free(org);
	free(b4);
	return (result);
}

char	*handle_exit_code(t_mini *mini, char *before, char *org, int *pos)
{
	char	*result;
	char	*temp;
	int		len;

	result = ft_itoa(mini->exit_status);
	len = ft_strlen(result);
	temp = ft_strjoin(before, result);
	free(result);
	result = ft_strjoin(temp, org + *pos + 2);
	*pos += len;
	free(temp);
	return (result);
}

char	*handle_invalid_char(t_env *env, char *temp, char *org, int *pos)
{
	if (org[*pos + 1] == '\'' || org[*pos + 1] == '$' || org[*pos + 1] == '\"')
		return (handle_dollar_sign_single(env, temp, org, pos));
	return (free(temp), (void)(*(pos))++, org);
}

char	*handle_dollar_sign(t_mini *mini, char *org, char *sub, int *pos)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		len;

	temp1 = ft_substr(org, 0, *pos);
	if (sub[1] == '?')
		return (handle_exit_code(mini, temp1, org, pos));
	if (is_valid_char(sub[1], true) == false)
		return (handle_invalid_char(mini->env, temp1, org, pos));
	len = 1;
	while (is_valid_char(sub[len], false) == true)
		len++;
	temp3 = ft_substr(org, *pos + 1, len - 1);
	temp2 = ft_getenv(mini->env, temp3);
	free(temp3);
	temp3 = ft_strjoin(temp1, temp2);
	len += handle_dollar_get_end(temp1 + ft_strlen(temp1));
	*pos += ft_strlen(temp2);
	free_many(temp1, temp2, 0, 0);
	temp1 = ft_substr(sub, len, ft_strlen(org));
	temp2 = ft_strjoin(temp3, temp1);
	free_many(temp1, temp3, org, 0);
	return (temp2);
}
