/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:47:27 by fmick             #+#    #+#             */
/*   Updated: 2025/04/22 11:37:07 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
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
}					t_type;

typedef struct s_re
{
	t_type			type;
	int				heredoc_fd;
	char			*str;
	struct s_re		*next;
}					t_re;

typedef struct s_line
{
	char			**command;
	t_re			*redirect;
	pid_t			*pid;
	int				pid_count;
	struct s_line	*next;
}					t_line;

typedef struct s_token
{
	char			*str;
	int				index;
	t_type			type;
	struct s_token	*next;
	struct s_token	*previous;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_extract
{
	int				start;
	int				len;
	bool			in_quotes;
	char			quote_char;
}					t_extract;

typedef struct s_mini
{
	int				exit_flag;
	int				exit_status;
	bool			interactive;

	int				nbr_of_pipes;
	int				fd_in;
	int				fd_out;
	int				pipe_in;
	int				pipe_out;
	int				stdin;
	int				stdout;
	int				fd;
	int				skibidi;

	char			**env_array;
	char			*path;

	t_line			*line;
	t_type			type;
	t_token			*token;
	t_env			*env;
	t_env			*export_env;
	t_extract		extract;
}					t_mini;

extern bool			g_skip;

// builtins
int					ft_is_builtin(char **av);
void				ft_handle_builtin(t_mini *mini);
int					ft_update_value(t_env *env, char *key, char *value);
int					ft_cd(char **av, t_env *env);
int					ft_echo(char **av);
void				ft_exit(t_mini *mini, char **cmd);
t_env				*ft_init_export_env_(char **envp);
int					ft_export_env(t_mini *mini, char **str);
void				ft_add_env_export(t_mini *mini, char *key, char *value);
int					ft_export(t_mini *mini, char **str);
int					ft_pwd(t_env *env);
int					ft_env(t_env *env);
void				ft_unset_key(t_env *env, char *key);
int					ft_unset(t_mini *mini, char **av);

// env
void				ft_shellvl(t_env *env);
int					ft_env_exists(t_env *env, char *key, char *value);
char				**ft_env_to_array(t_env *env);
char				*ft_getenv(t_env *env, char *key);
void				ft_env_display(t_env *env);
char				**ft_split_env(char *str);
t_env				*ft_add_env_node(char *key, char *value);
t_env				*ft_init_env(char **envp);

// exec
void				ft_execute_pipeline(t_mini *mini);
void				ft_single_command(t_mini *mini);
void				ft_execute_command(t_mini *mini);

// externals
char				*check_external(t_mini *mini, t_env *env, char *command);
int					ft_handle_external(t_mini *mini, char **args);

// heredocs
void				ft_heredoc_child(t_mini *mini, t_re *redir, int *pipefd);
void				ft_handle_heredoc(t_mini *mini, t_re *redir);
void				ft_pipe_heredoc(t_mini *mini, t_line *current);
void				ft_execute_heredoc(t_mini *mini);

// pipes
void				ft_piping(t_mini *mini, t_line *current);
void				ft_execute_child(t_mini *mini, t_line *current);
void				ft_fork_and_exe(t_mini *mini, t_line *current, pid_t *pids,
						int i);
void				ft_piped_cmd(t_mini *mini, t_line *current, pid_t *pids,
						int i);

// redirections
void				ft_handle_redirections(t_mini *mini);
void				ft_handle_input_redir(t_mini *mini, t_re *redir);
void				ft_handle_output_redir(t_mini *mini, t_re *redir);

// signal
void				ft_handle_sigint(int signal);
void				handle_signals(void);

// utils
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_find_key(t_env *env, char *key);
int					ft_has_equal(t_mini *mini, char *str);

// utils erros
void				ft_error(t_mini *mini, char **cmd, int i, int error);
int					ft_cd_error(char *path, int error);
void				ft_error_syntax(t_mini *mini, char *token);
void				ft_print_error(t_mini *mini, char *line, char *msg,
						int exit);
void				ft_error_msg(t_mini *mini);
bool				ft_handle_token_error(t_mini *mini, t_token *current);

// utils pipes
void				ft_restore_std_fds(t_mini *mini);
void				ft_close(int fd);
void				ft_supersafe_close(int fd);
void				ft_safe_dup2(int oldfd, int newfd);
int					ft_wait(t_mini *mini, pid_t *pids, int i);

// parser
int					is_operator_char(char c);
t_type				get_operator_type(char *op, int len);
t_token				*if_operator(t_token *token, char *input, int *i);
bool				is_valid_char(char c, bool first);
bool				exit_validity(t_line *line);
bool				echo_validity(char *str);
bool				export_validity(char *str);
bool				token_validity(t_mini *mini);
size_t				calculate_number_of_commands(t_token *token);
size_t				count_pipes(t_token *token);
void				init_extract(t_extract *extract, int pos);
char				*check_unclosed_quote(t_extract *extract, int *pos,
						char *input);
char				*extract_word(t_extract *extract, char *input, int *pos);
t_token				*find_pipe(t_token *token);
t_token				*find_command(t_token *token);
int					handle_dollar_get_end(char *str);
char				*handle_dollar_sign_single(t_env *env, char *b4, char *org,
						int *pos);
char				*handle_exit_code(t_mini *mini, char *before, char *org,
						int *pos);
char				*handle_invalid_char(t_env *env, char *temp, char *org,
						int *pos);
char				*handle_dollar_sign(t_mini *mini, char *org, char *sub,
						int *pos);
char				*if_empty_quote(char *before, char *sub, int len,
						char *org);
char				*handle_single_quote(char *org, char *sub, int *pos);
char				*check_double_quote_variable(t_mini *mini, char *org,
						int *pos);
char				*handle_double_quote(t_mini *mini, char *org, char *sub,
						int *pos);
void				expand_variables(t_mini *mini);
t_line				*structurize_line(t_mini *mini);
void				parse_string(t_mini *mini, char *line);
t_re				*add_node_redirect(t_token *token);
t_re				*structurize_redirect(t_token *token);
char				**make_command_into_array(t_token *token);
t_line				*add_node_line(t_token *token);
void				arguments_before_pipe(t_token *token);
void				find_redirect(t_token *token);
void				token_relativity(t_token *token);
t_token				*find_last_token(t_token *token);
t_token				*add_node_token(t_token *token, char *str, t_type type);
void				remove_empty_tokens(t_mini *mini);
t_token				*tokenize_input(t_mini *mini, char *input);

// main
void				ft_mini_init(t_mini *mini);
int					ft_parse_input(t_mini *mini);
int					main(int ac, char **av, char **envp);

// clean up
void				free_many(char *str1, char *str2, char *str3, char *str4);
void				free_env(t_env *env);
void				free_redirect(t_re *redirect);
void				line_cleanup(t_mini *mini);
void				free_mini(t_mini *mini);

#endif
