/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:47:27 by fmick             #+#    #+#             */
/*   Updated: 2025/04/15 13:47:06 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>

// colours
# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define RESET "\033[0m"


# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
	APPEND_OUTFILE = 10,
}	t_type;

typedef struct s_re
{
	t_type		type;
	int			heredoc_fd;
	char		*str;
	struct s_re	*next;
}	t_re;


typedef struct s_line
{
	char		**command;
	t_re		*redirect;
	pid_t		*pid;
	int			pid_count;
	struct s_line	*next;
}	t_line;

typedef struct s_token
{
	char			*str;
	int				index;
	t_type			type;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_extract
{
	int		start;
	int		len;
	bool	in_quotes;
	char	quote_char;
}	t_extract;

typedef struct s_mini
{
    int			exit_flag;
	int			exit_status;
	bool		interactive;


	int			nbr_of_pipes;
	int			fd_in;
	int			fd_out;
	int			pipe_in;
	int			pipe_out;	
	int			stdin;
	int			stdout;
	int			fd;
	int		    skibidi;

	char		**env_array;
	char		*path;

    t_line		*line;
    t_type		type;
    t_token		*token;
    t_env		*env;
	t_env		*export_env;
	t_extract	extract;
}	t_mini;


// utils - not in use
void	print_tokens(t_token *token);
void	print_lines(t_line *line);

//tokens
void	token_relativity(t_token *token);
bool	token_validity(t_mini *mini);
t_token	*tokenize_input(t_mini *mini, char *input);
t_token	*find_last_token(t_token *token);
t_token	*add_node_token(t_token *token, char *str, t_type type);
size_t	count_pipes(t_token *token);
t_line	*add_node_line(t_token *token);
t_token	*find_pipe(t_token *token);
size_t	calculate_number_of_commands(t_token *token);
t_token	*find_command(t_token *token);
t_token	*if_operator(t_token *token, char *input, int *i);
t_token	*find_last_token(t_token *token);



//parse
void	parse_string(t_mini *mini, char *line);
char	*handle_single_quote(char *org, char *sub, int *pos);
char	*handle_double_quote(t_mini *mini, char *org, char *sub, int *pos);
char	*handle_dollar_sign(t_mini *mini, char *org, char *sub, int *pos);
void	line_cleanup(t_mini *mini);
void	free_many(char *str1, char *str2, char *str3, char *str4);
bool	is_valid_char(char c, bool first);
bool	export_validity(char *str);
t_line	*structurize_line(t_mini *mini);
bool	token_validity(t_mini *mini);
bool	echo_validity(char *str);



char	*check_external(t_mini *mini, t_env *env, char *command);

bool	exit_validity(t_line *line);

int	is_operator_char(char c);

char	*extract_word(t_extract *extract, char *input, int *pos);

void	expand_variables(t_mini *mini);



// fmick
// utils
//void				ft_putstr_fd(char *str, int fd);
int					ft_strcmp(const char *s1, const char *s2);
//char				*ft_strdup(const char *s1);

// builtins
int					ft_is_builtin(char **av);
void				ft_handle_builtin(t_mini *mini);
int					ft_pwd(t_env *env);
int					ft_echo(char **av);
int					ft_env(t_env *env);
int					ft_unset(t_mini *mini, char **av);
int					ft_export(t_mini *mini, char **str);
int					ft_env_exists(t_env *env, char *key, char *value);
int					ft_update_value(t_env *env, char *key, char *value);
int					ft_cd(char **av, t_env *env);


// redirections
void 	ft_handle_redirections(t_mini *mini);
void    ft_handle_input_redir(t_mini *mini, t_re *redir);
void	ft_handle_output_redir(t_mini *mini, t_re *redir);
void 	ft_handle_here_doc(t_mini *mini, t_re *redir, int index);

// env
void				ft_env_display(t_env *env);
t_env				*ft_add_env_node(char *key, char *value);
t_env				*ft_init_env(char **envp);
char    			*ft_getenv(t_env *env, char *key);
char				*ft_find_key(t_env *env, char *key);
char    			*ft_update_key(t_env *env, char *key, char *new_value);
void    			ft_unset_key(t_env *env, char *key);
int					ft_setenv(t_env *env, const char *key,
						const char *new_value, int overwrite);
void	free_env(t_env *env);

// signal
void				ft_handle_sigint(int signal);
int					ft_get_g_global(void);
void				handle_signals(void);

int		ft_parse_input(t_mini *mini);
void ft_cleanup_pipes(t_mini *mini);
void ft_allocate_pipes(t_mini *mini);


void    ft_exit(t_mini *mini, char **cmd);
char **ft_env_to_array(t_env *env);


int	ft_handle_external(t_mini *mini, char **args);
void	ft_execute_command(t_mini *mini);

// int ft_handle_heredoc(t_mini *mini, t_re *redir);
void ft_handle_heredoc(t_mini *mini, t_re *redir);
void ft_heredoc_child(t_mini *mini, t_re *redir, int *pipefd);
void ft_close_heredoc_fds(t_mini *mini);
void ft_execute_pipeline(t_mini *mini);
void ft_preprocess_heredocs(t_mini *mini);

void	ft_close(int fd);
void	ft_mini_init(t_mini *mini);

void ft_allocate_pipes(t_mini *mini);
void ft_wait_for_children(t_mini *mini);
void ft_handle_prev_fd(int prev_fd);

void ft_handle_pipes(t_mini *mini);
void ft_fork_processes(t_mini *mini);
void ft_allocate_pipes(t_mini *mini);
void ft_cleanup_pipes(t_mini *mini);
void ft_close_all_pipes(t_mini *mini, int index);
void    ft_pipe_heredoc(t_mini *mini, t_line *current);

void ft_restore_std_fds(t_mini *mini);
void	close_pipe_fds(t_mini *mini, int skip_index);
bool	create_pipes(t_mini *mini);
bool	set_pipe_fds(t_mini *mini, int index);
void ft_handle_parent(t_mini *mini, t_line *current);
void ft_execute_child(t_mini *mini, t_line *current);
void	ft_redir_output(t_line *current, int pipe_fds[2]);
void	ft_fork_and_exe(t_mini *mini, t_line *current, pid_t *pids, int i);
void ft_execute_heredoc(t_mini *mini);
void	ft_error_msg(t_mini *mini);

t_env	*ft_init_export_env_(char **envp);
int	ft_export_env(t_mini *mini, char **str);

void	ft_safe_dup2(int oldfd, int newfd);
void	ft_close(int fd);
void	ft_single_command(t_mini *mini);

/*
TODO
-- exit flags/status
-- env add node ignore every = after first one
-- symbolic link (leaving)
-- expansions with
*/


# endif
