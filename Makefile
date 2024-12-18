CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBS = -lmlx_Linux -lXext -lX11 -lm -lz
SRC = $(wildcard src/*.c)
NAME = fdf  

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	$(CC) $(SRC:.c=.o) -Lmlx_linux -L/usr/lib -Imlx_linux $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm $(SRC:.c=.o)

fclean: clean
	rm $(NAME)

re: fclean all