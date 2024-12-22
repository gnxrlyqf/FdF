# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 14:27:45 by mchetoui          #+#    #+#              #
#    Updated: 2024/11/04 17:30:34 by mchetoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
SRC = $(wildcard *.c)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	ar rcs libft.a $?

%.o: %.c
	$(CC) $(CFLAGS) -I../incluldes -o $@ -c $<

clean:
	rm -rf $(FILES:.c=.o)

fclean: clean
	rm -rf libft.a

re: fclean all