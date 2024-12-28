CC = cc
WINDOW_SIZE = 720
CFLAGS = -Wall -Werror -Wextra -g
LIB = -L./minilibx-linux -L./libft -lft -lmlx -lXext -lX11 -lm -lz
INC = -I./minilibx-linux -I./includes
SRC = $(wildcard src/*.c)
NAME = fdf

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(SRC:.c=.o) lib
	$(CC) $(SRC:.c=.o) $(INC) $(LIB) -o $(NAME)

lib:
	make -C minilibx-linux/ -f Makefile.mk
	make -C libft/

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -O3 -c $< -o $@ -DWIN=$(WINDOW_SIZE)

clean:
	rm -rf $(SRC:.c=.o)

fclean: clean
	rm -rf $(NAME)
	make -C minilibx-linux/ -f Makefile.mk clean
	make -C libft/ -f Makefile fclean

re: fclean all