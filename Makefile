# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/05 14:20:07 by dchirol           #+#    #+#              #
#    Updated: 2017/05/14 16:32:36 by dchirol          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG=true

NAME = ft_ls

SRC = src/ft_ls.c src/main.c src/utilities.c

CC = gcc
ifeq ($(DEBUG), true)
	CFLAGS = -I includes -g
else
	CFLAGS = -Wall -Wextra -Werror -I includes
endif
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@gcc -o $@ $^ libft.a

clean:
	/bin/rm -f $(OBJ)

fclean: clean

re : clean all
