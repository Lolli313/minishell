/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:47:27 by fmick             #+#    #+#             */
/*   Updated: 2025/03/13 16:28:14 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

// colours
# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define RESET "\033[0m"

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
}	t_type;

typedef struct s_redirect
{
	t_type		type;
	char		*str;
	struct s_re	*next;
}	t_redirect;

typedef struct s_line
{
	char		**command;
	/*char		**infile;
	char		**delimiter;
	int			infile_or_delimiter;
	char		**outfile;
	char		**append;
	int			outfile_or_append;*/
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
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_mini
{
    int			exit_flag;
    char		*infile;
    char		*outfile;
    int			stdin;
    int			stdout;
    int			pid;
    t_line		*line;
    t_type		type;
    t_token		*token;
    t_env		*env;
}                    t_mini;

void	parse_string(t_mini *mini, char *line);

t_token	*tokenizer(char *str, t_type type, t_token *token);

void	token_relativity(t_token *token);

t_line	*structurize_line(t_token *token, t_line *line);

t_env	*init_env(char **envp);

#endif