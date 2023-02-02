# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pperol <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 11:03:01 by pperol            #+#    #+#              #
#    Updated: 2023/02/02 11:07:34 by pperol           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = 	main.c

CC = clang

INC = minishell.h

CFLAGS = -Weverything

LFLAGS = -valgrind -g

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LFLAGS) -o $(NAME)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
