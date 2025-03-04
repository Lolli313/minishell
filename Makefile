# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 08:55:32 by fmick             #+#    #+#              #
#    Updated: 2025/03/04 16:21:37 by aakerblo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -g -Wall -Wextra -Werror
DEPS = -Iinclude
SRCDIR = ./src/
SRC = $(SRCDIR)main.c $(SRCDIR)parse.c $(SRCDIR)env.c
LIBS = -lreadline -lhistory
LIBFTDIR = ./libft/
LIBFT = $(LIBFTDIR)libft.a
OBJDIR = obj/
OBJ = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

default: all

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	cc $(CFLAGS) -c $< -o $@ $(DEPS)

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