/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:47:27 by fmick             #+#    #+#             */
/*   Updated: 2025/03/18 10:14:21 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
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

// tokenazation
typedef enum e_type
{
	COMMAND = 0,
	ARGUMENT = 1,
	RE_INPUT = 2,
	RE_OUTPUT = 3,
	RE_APPEND = 4,
	PIPE = 5,
	HERE_DOC = 6,
	LIMITER = 7,
	INFILE = 8,
	OUTFILE = 9,
}					t_type;

typedef struct s_redirect
{
	t_type		type;
	char		*str;
	struct s_re	*next;
}	t_redirect;

typedef struct s_line
{
	char		**command;
	t_redirect	*redirect;
	struct s_line	*next;
}	t_line;

typedef struct s_token
{
	char			*str;
	int				index;
	t_type			type;
	struct s_token	*next;
	struct s_token	*previous;
}					t_token;

typedef struct s_extract
{
	int		start;
	int		len;
	bool	in_quotes;
	char	quote_char;
}	t_extract;

// USER=fmick ---> (USER = key) & (fmick = value)
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_mini
{
    int			exit_flag;
    char		*infile;
    char		*outfile;
	int			nbr_of_pipes;
    int			pid;
    t_line		*line;
    t_type		type;
    t_token		*token;
    t_env		*env;
	t_extract	extract;
}	t_mini;

// utils
void				ft_putstr_fd(char *str, int fd);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s1);

// builtins
int					ft_is_builtin(char **av);
void				ft_handle_builtin(char **av, t_mini *mini);
int					ft_pwd(void);
int					ft_echo(char **av);
int					ft_env(t_env *env);
int					ft_unset(t_mini *mini, char **av);
int	ft_export(t_env **env, char *str);
int					ft_env_exists(t_env *env, char *key, char *value);
int					ft_update_value(t_env *env, char *key, char *value);
void				ft_cd(char **av, t_env *env);

// pipe managment
void	ft_handle_pipes(t_mini *mini);

// events
void				ft_env_display(t_env *env);
t_env				*ft_add_env_node(char *key, char *value);
t_env				*ft_init_env(char **envp);
char				*ft_get_env(const char *key, t_env *env);
char				*ft_find_key(t_env *env, char *key);
char    			*ft_update_key(t_env *env, char *key, char *new_value);
void    			ft_unset_key(t_env *env, char *key);
int					ft_setenv(t_env *env, const char *key,
						const char *new_value, int overwrite);

// signal
void				ft_handle_sigint(int signal);
int					ft_get_g_global(void);

#endif
