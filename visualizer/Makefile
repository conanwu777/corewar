NAME = corewar
CC = @gcc
CFLAGS = -O2 -Wall -Wextra -Werror
SRC = display.c display_info.c visual_support.c main.c setup.c support.c update.c freers.c\
	functions1.c functions2.c functions3.c functions4.c functions5.c
OBJ = $(SRC:.c=.o)
FT_LNK = -L ../libft -lft
GRAPHICS = -framework OpenGL -framework AppKit -lpthread
MLX_LNK = -L ./minilibx_macos -lmlx

$(NAME): $(OBJ) libft/libft.a
	@echo "Building Corewar"
	$(CC) $(CFLAGS) $(MLX_LNK) $(GRAPHICS) $(FT_LNK) $(OBJ) -o $(NAME)

libft/libft.a:
	@make -C ../libft

all: $(NAME)

clean:
	@/bin/rm -f $(OBJ)
	@make clean -C ../libft

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C ../libft

all: $(NAME)

re:	fclean all
