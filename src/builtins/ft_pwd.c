/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:19 by fmick             #+#    #+#             */
/*   Updated: 2025/04/09 10:02:40 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

int	ft_pwd(t_env *env)
{
	char	*cwd;
	char	buffer[4096];

	cwd = ft_find_key(env, "PWD");
	if (cwd)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		if (getcwd(buffer, sizeof(buffer)) != NULL)
		{
			printf("%s\n", buffer);
			return (0);
		}
		else
		{
			perror("pwd");
			return (-1);
		}
	}
}
