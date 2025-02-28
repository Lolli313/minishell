/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:47:27 by fmick             #+#    #+#             */
/*   Updated: 2025/02/28 11:30:01 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unisdt.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>


// colours
# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define RESET "\033[0m"


//utils
int	strcmp(const char *s1, const char *s2);

//builtin/external commands
int	ft_handle_builtin(char **av);
int	ft_handle_external(char **av);
void	ft_execute_command(char **av);
