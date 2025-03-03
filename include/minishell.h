/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:47:27 by fmick             #+#    #+#             */
/*   Updated: 2025/03/03 16:23:14 by aakerblo         ###   ########.fr       */
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

enum e_type
{
	COMMAND = 0,
	ARGUMENTS = 1,
	RE_INPUT = 2,
	RE_OUTPUT = 3,
	APPEND = 4,
	PIPE = 5,
	HERE_DOC = 6,
};

typedef struct s_token
{
	char			*str;
	int				index;
	enum e_type		type;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

void	parse_string(char *line);

t_token	tokenizer(char *str, int type, t_token *token);

void	initialize(t_token *token);

t_token	*add_node_token(char *str, t_token *token, int type);

#endif