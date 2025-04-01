# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmick <fmick@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 08:55:32 by fmick             #+#    #+#              #
#    Updated: 2025/04/01 11:09:39 by fmick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
CFLAGS		=	-g -Wall -Wextra -Werror -fpie
SRC 		=	$(addprefix src/env/, ft_env.c \
				ft_env_utils.c) \
				$(addprefix src/builtins/, ft_cd.c \
				ft_echo.c \
				ft_pwd.c \
				ft_export.c \
				ft_env.c \
				ft_unset.c \
				ft_exit.c \
				ft_builtins.c) \
				$(addprefix src/, main.c \
				ft_utils_1.c \
				ft_signals.c \
				cleanup.c \
				parse.c \
				check_operator.c \
				check_validity.c \
				count_functions.c \
				extract_word.c \
				find_functions.c \
				handle_dollar.c \
				handle_quotes.c \
				structurize_line.c \
				token_relativity.c \
				tokenizer.c \
				print_functions.c) \
				$(addprefix src/exe/, ft_pipes.c \
				ft_redir.c \
				ft_externals.c \
				ft_heredoc.c) \

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
