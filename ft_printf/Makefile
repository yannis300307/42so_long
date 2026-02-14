CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a
SRC = ft_printf.c     \
	  ft_printf.c     \
	  put_nbr.c       \
	  put_ptr.c       \
	  put_str.c       \
	  puthex.c        \


OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	ar rcs $@ $^
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
