# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmick <fmick@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 08:55:32 by fmick             #+#    #+#              #
#    Updated: 2025/03/18 14:07:07 by fmick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		=	minishell
CFLAGS 		=	-g -Wall -Wextra -Werror -fpie
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
				$(addprefix src/, minishell.c \
				ft_execution.c \
				ft_utils_1.c \
				ft_signals.c)
LIBS 		=	-lreadline -lhistory
LIBFTDIR 	=	libft/
LIBFT 		=	$(LIBFTDIR)libft.a
OBJDIR 		=	obj/
OBJ 		=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

INCLUDES	=	-I includes -I libft

default: all

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

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
