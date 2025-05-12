# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 08:55:32 by fmick             #+#    #+#              #
#    Updated: 2025/05/12 13:18:07 by aakerblo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
CFLAGS		=	-g -Wall -Wextra -Werror
SRC 		=	$(addprefix src/builtins/, ft_builtins.c \
						ft_cd.c \
						ft_echo.c \
						ft_env.c \
						ft_exit.c \
						ft_export.c \
						ft_pwd.c \
						ft_unset.c) \
				$(addprefix src/env/, ft_env.c \
						ft_env_utils.c) \
				$(addprefix src/exe/, ft_externals.c \
						ft_heredoc.c \
						ft_heredoc2.c \
						ft_pipes.c \
						ft_redir.c \
						ft_execute.c) \
				$(addprefix src/parser/, check_operator.c \
						check_validity.c \
						cleanup.c \
						count_functions.c \
						extract_word.c \
						find_functions.c \
						ft_signals.c \
						ft_signals2.c \
						handle_dollar.c \
						handle_quotes.c \
						parse.c \
						structurize_line.c \
						token_relativity.c \
						tokenizer.c) \
				$(addprefix src/utils/, ft_close.c \
						ft_errors.c \
						ft_pipes_utils.c \
						ft_utils_1.c) \
				$(addprefix src/, main.c) \


LIBS 		= 	-lreadline -lhistory
LIBFTDIR 	= 	libft/
LIBFT 		= 	$(LIBFTDIR)libft.a
OBJDIR 		= 	obj/
OBJ 		= 	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
INCLUDE		=	-Iinclude -Ilibft

R = \033[1;31m
G = \033[1;32m
Y = \033[1;33m
B = \033[1;34m
RESET = \033[0m

default: all

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@echo -e "$(G)Building Project successfull$(RESET)"
	cc $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME): $(OBJ)
	make -C $(LIBFTDIR)
	cp $(LIBFT) $(NAME)
	cc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBS)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

$(LIBFT):
	make -C $(LIBFTDIR) all

$(OBJDIR):
	mkdir -p $(OBJDIR)

PHONY: all clean fclean re
