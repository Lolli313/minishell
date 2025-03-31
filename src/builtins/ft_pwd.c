/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:19 by fmick             #+#    #+#             */
/*   Updated: 2025/03/31 08:18:41 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*"getcwd(NULL, 0) asks the system to allocate
enough memory to store the current working directory
and returns a pointer to it. The memory is dynamically allocated,
so you don't need a predefined maximum length like PATH_MAX.
which is unreliable due to system-dependent values between OSs
and isnt guaranteed to work with all file systems"*/
int	ft_pwd(t_env *env)
{
	char	*cwd;
	cwd = ft_find_key(env, "PWD"); // NULL allows getcwd to allocate the buffer
	if (cwd)
	{
		printf("%s\n", cwd);
		return (0); // success
	}
	else
	{
		char buffer[PATH_MAX];
        if (getcwd(buffer, sizeof(buffer)) != NULL)
        {
            printf("%s\n", buffer);
            return (0); // success
        }
        else
        {
            perror("pwd");
            return (-1); // failure
        }
	}
}
