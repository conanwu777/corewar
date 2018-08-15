NAME = asm
CC = @gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ops.c main.c helpers.c labels.c name_comments.c
OBJ = $(SRC:.c=.o)

FT_LNK = -L ../libft -lft

.PHONY: clean fclean all re

$(NAME): $(OBJ) libft/libft.a
	@echo "Building asm"
	$(CC) $(CFLAGS) $(FT_LNK) $(OBJ) -o $(NAME)

libft/libft.a:
	@make -C ../libft

clean:
	@echo "Cleaning"
	@rm -f $(OBJ)
	@make clean -C ../libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ../libft

all: $(NAME)

re:	fclean all
