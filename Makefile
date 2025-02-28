# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 08:55:32 by fmick             #+#    #+#              #
#    Updated: 2025/02/28 17:54:16 by aakerblo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -g -Wall -Wextra -Werror
DEPS = -Iinclude
SRCDIR = ./src/
SRC = $(SRCDIR)main.c
OBJDIR = obj/
OBJ = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

default: all

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	cc $(CFLAGS) -c $< -o $@ $(DEPS)

$(NAME): $(OBJ)
	cc $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJDIR):
	mkdir -p $(OBJDIR)

PHONY: all clean fclean re