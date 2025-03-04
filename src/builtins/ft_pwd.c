/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:19 by fmick             #+#    #+#             */
/*   Updated: 2025/03/04 09:25:24 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*"getcwd(NULL, 0) asks the system to allocate
enough memory to store the current working directory
and returns a pointer to it. The memory is dynamically allocated,
so you don't need a predefined maximum length like PATH_MAX.
which is unreliable due to system-dependent values between OSs
and isnt guaranteed to work with all file systems"*/
int	ft_pwd(void)
{
	char	*cwd;
	cwd = getcwd(NULL, 0); // NULL allows getcwd to allocate the buffer
	if (cwd)
	{
		free(cwd);
		return (0); // success
	}
	else
	{
		// error
		return (-1); // error
	}
	
	return (0);
}
