# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pperol <pperol@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 11:03:01 by pperol            #+#    #+#              #
#    Updated: 2023/02/07 10:51:17 by pperol           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC = 	main.c ft_automate.c

CC = clang

INC = minishell.h

CFLAGS = -Weverything

LFLAGS = -lreadline

# valgrind --suppressions=cmd_valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell

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
