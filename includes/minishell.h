/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:47:27 by fmick             #+#    #+#             */
/*   Updated: 2025/03/04 13:33:02 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <unistd.h>

// colours
# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define RESET "\033[0m"

// keys
# define arrow_up "\033[A"
# define arrow_down "\033[B"

// USER=fmick ---> (USER = key) & (fmick = value)
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}   t_env;

typedef struct s_mini
{
	// t_token	*token;
	char	*env_lst;
	t_env	*env;
}			t_mini;

// utils
void		ft_putstr_fd(char *str, int fd);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);

// builtins
int			ft_is_builtin(char **av);
int			ft_pwd(void);
int			ft_echo(char **av);
void		ft_handle_builtin(char **av);
