NAME = libft.a

CC = cc
FLAGS = -Wall -Werror -Wextra -I. -I../
INCLUDE = ../fractol.h
OBJ_DIR = obj
LIB_SRC = libft/ft_strncmp.c libft/ft_putstr_fd.c libft/ft_atodbl.c

SRC = $(LIB_SRC)
OBJ = $(patsubst libft/%.c, $(OBJ_DIR)/libft/%.o, $(LIB_SRC)) \

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/libft/%.o: libft/%.c $(INCLUDE)
	mkdir -p $(OBJ_DIR)/libft
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/printf/%.o: printf/%.c $(INCLUDE)
	mkdir -p $(OBJ_DIR)/printf
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re