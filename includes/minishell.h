/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:47:27 by fmick             #+#    #+#             */
/*   Updated: 2025/03/06 12:07:08 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <readline/history.h>
#include <readline/readline.h>

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
	// char			*key_value;
	struct s_env	*next;
}   t_env;

typedef struct s_mini
{
	int		exit_flag;
	// t_token	*token;
	t_env	*env_lst;
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
int			ft_env(t_env *env);
int	ft_export(t_env *env, char *key, char *value);
int	ft_env_exists(t_env *env, char *key, char *value);
void		ft_handle_builtin(char **av, t_mini *mini);
char	*ft_find_key(t_env	*env, char *key);
int		ft_update_value(t_env *env, char *key, char *value);
void	ft_cd(char **av, t_env *env);

// events
void	ft_env_display(t_env *env);
t_env	*ft_add_env_node(char **array);
t_env	*ft_init_env(char **envp);
char	*ft_get_env(const char *key, t_env *env);
int		ft_setenv(t_env *env, const char *key, const char *new_value, int overwrite);

// signal
void	ft_handle_sigint(int signal);
int	ft_get_g_global(void);


#endif
