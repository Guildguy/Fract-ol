NAME = fractol

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -I. -Iminilibx-linux
LDFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
LIBFT_DIR = Libft
LIBFT_A = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX_A = $(MLX_DIR)/libmlx.a
OBJ_DIR = obj
SRC_DIRS = Files/
SRCS = $(wildcard $(SRC_DIRS)/*.c)
OBJS = $(patsubst $(SRC_DIRS)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	$(CC) $(OBJS) $(LIBFT_A) $(MLX_A) $(LDFLAGS) -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIRS)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re