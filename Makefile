NAME = fractol

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iminilibx-linux
LDFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
LIBFT_DIR = Libft
LIBFT_A = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX_TGZ = minilibx-linux.tgz
MLX_A = $(MLX_DIR)/libmlx.a
OBJ_DIR = obj
SRC_DIR = srcs
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Docker
DOCKER_IMAGE = fractol:latest
DOCKER_COMPOSE = docker-compose

# Cores
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

# ============================================================================ #
#                                 MAIN TARGETS                                 #
# ============================================================================ #

all: check-deps $(NAME)

$(NAME): $(MLX_A) $(LIBFT_A) $(OBJS)
	@echo "$(GREEN)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"

check-deps:
	@echo "$(BLUE)🔍 Verificando dependências...$(RESET)"
	@if ! command -v pkg-config >/dev/null 2>&1; then \
		echo "$(YELLOW)⚠️  pkg-config não encontrado. Tentando verificação alternativa...$(RESET)"; \
		if ! test -f /usr/include/X11/Xlib.h; then \
			echo "$(RED)❌ ERRO: Bibliotecas X11 não encontradas!$(RESET)"; \
			echo ""; \
			echo "$(YELLOW)Para instalar as dependências, execute:$(RESET)"; \
			echo "  $(GREEN)make install-deps$(RESET)"; \
			echo ""; \
			exit 1; \
		fi; \
	elif ! pkg-config --exists x11 2>/dev/null; then \
		echo "$(RED)❌ ERRO: Bibliotecas X11 não encontradas!$(RESET)"; \
		echo ""; \
		echo "$(YELLOW)Para instalar as dependências, execute:$(RESET)"; \
		echo "  $(GREEN)make install-deps$(RESET)"; \
		echo ""; \
		exit 1; \
	fi
	@echo "$(GREEN)✅ Dependências OK!$(RESET)"

$(LIBFT_A):
	@echo "$(BLUE)📚 Compiling Libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX_DIR):
	@if [ -f $(MLX_TGZ) ]; then \
		echo "$(YELLOW)📦 Extracting $(MLX_TGZ)...$(RESET)"; \
		tar -xzf $(MLX_TGZ); \
		echo "$(GREEN)✅ MiniLibX extracted!$(RESET)"; \
	else \
		echo "$(RED)❌ Error: $(MLX_TGZ) not found!$(RESET)"; \
		exit 1; \
	fi

$(MLX_A): $(MLX_DIR)
	@echo "$(BLUE)🎨 Compiling MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@echo "$(GREEN)✅ MiniLibX compiled!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@


# ============================================================================ #
#                            INSTALLATION TARGETS                              #
# ============================================================================ #

install-deps:
	@echo "$(BLUE)📦 Instalando dependências do sistema...$(RESET)"
	@chmod +x docker-config/tools/install_dependencies.sh
	@./docker-config/tools/install_dependencies.sh

# ============================================================================ #
#                                CLEAN TARGETS                                 #
# ============================================================================ #

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) --no-print-directory
	@if [ -d $(MLX_DIR) ]; then \
		$(MAKE) clean -C $(MLX_DIR) --no-print-directory; \
	fi
	@echo "$(GREEN)✅ Clean complete!$(RESET)"

fclean: clean
	@echo "$(YELLOW)🧹 Removing executable and libraries...$(RESET)"
	@rm -rf $(NAME) $(MLX_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ Full clean complete!$(RESET)"

mlx-fclean:
	@echo "$(YELLOW)🧹 Removing MiniLibX directory...$(RESET)"
	@rm -rf $(MLX_DIR)
	@echo "$(GREEN)✅ MiniLibX removed!$(RESET)"

re: fclean all

# ============================================================================ #
#                                DOCKER TARGETS                                #
# ============================================================================ #

docker-build:
	@echo "$(BLUE)🐳 Building Docker image...$(RESET)"
	@docker build -f docker-config/Dockerfile -t $(DOCKER_IMAGE) .
	@echo "$(GREEN)✅ Docker image built!$(RESET)"

docker-run-mandelbrot: docker-build
	@echo "$(GREEN)🚀 Running Mandelbrot in Docker...$(RESET)"
	@chmod +x docker-config/tools/run_docker.sh
	@./docker-config/tools/run_docker.sh mandelbrot

docker-run-julia: docker-build
	@echo "$(GREEN)🚀 Running Julia set in Docker...$(RESET)"
	@chmod +x docker-config/tools/run_docker.sh
	@./docker-config/tools/run_docker.sh julia 0.285 0.01

docker-shell: docker-build
	@echo "$(BLUE)🐚 Opening shell in Docker container...$(RESET)"
	@docker run --rm -it \
		-e DISPLAY=$(DISPLAY) \
		-v /tmp/.X11-unix:/tmp/.X11-unix:rw \
		$(DOCKER_IMAGE) /bin/bash

docker-compose-up:
	@echo "$(BLUE)🐳 Starting with Docker Compose...$(RESET)"
	@xhost +local:docker > /dev/null 2>&1
	@$(DOCKER_COMPOSE) -f docker-config/docker-compose.yml up --build

docker-compose-down:
	@echo "$(YELLOW)⬇️  Stopping Docker Compose...$(RESET)"
	@$(DOCKER_COMPOSE) -f docker-config/docker-compose.yml down
	@xhost -local:docker > /dev/null 2>&1
	@echo "$(GREEN)✅ Docker Compose stopped!$(RESET)"

docker-clean:
	@echo "$(RED)🧹 Cleaning Docker images and containers...$(RESET)"
	@docker rmi $(DOCKER_IMAGE) 2>/dev/null || true
	@$(DOCKER_COMPOSE) -f docker-config/docker-compose.yml down -v 2>/dev/null || true
	@echo "$(GREEN)✅ Docker cleaned!$(RESET)"

# ============================================================================ #
#                                  HELP TARGET                                 #
# ============================================================================ #

help:
	@echo ""
	@echo "$(BLUE)╔═══════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║                    FRACTOL - MAKEFILE HELP                        ║$(RESET)"
	@echo "$(BLUE)╚═══════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(GREEN)📋 PASSO A PASSO - PRIMEIRA VEZ (COMPILAÇÃO LOCAL):$(RESET)"
	@echo "  $(YELLOW)1.$(RESET) make install-deps  → Instala dependências do sistema"
	@echo "  $(YELLOW)2.$(RESET) make               → Descompacta minilibx + compila tudo"
	@echo "  $(YELLOW)3.$(RESET) ./fractol mandelbrot  → Executa o fractal Mandelbrot"
	@echo "  $(YELLOW)4.$(RESET) ./fractol julia 0.285 0.01  → Executa o fractal Julia"
	@echo ""
	@echo "$(GREEN)🐳 PASSO A PASSO - PRIMEIRA VEZ (DOCKER - RECOMENDADO):$(RESET)"
	@echo "  $(YELLOW)1.$(RESET) make docker-build          → Cria imagem Docker"
	@echo "  $(YELLOW)2.$(RESET) make docker-run-mandelbrot → Executa Mandelbrot"
	@echo ""
	@echo "$(GREEN)🔨 COMPILAÇÃO LOCAL:$(RESET)"
	@echo "  $(YELLOW)make install-deps$(RESET) → Instala dependências (X11, etc)"
	@echo "  $(YELLOW)make$(RESET)              → Compila o projeto completo"
	@echo "  $(YELLOW)make re$(RESET)           → Recompila tudo do zero"
	@echo "  $(YELLOW)make clean$(RESET)        → Remove arquivos objeto (.o)"
	@echo "  $(YELLOW)make fclean$(RESET)       → Remove tudo (executável + .o)"
	@echo "  $(YELLOW)make mlx-fclean$(RESET)   → Remove o diretório minilibx-linux"
	@echo ""
	@echo "$(BLUE)🐳 DOCKER - MODO FÁCIL (recomendado):$(RESET)"
	@echo "  $(YELLOW)make docker-build$(RESET)           → Cria imagem Docker"
	@echo "  $(YELLOW)make docker-run-mandelbrot$(RESET)  → Roda Mandelbrot no Docker"
	@echo "  $(YELLOW)make docker-run-julia$(RESET)       → Roda Julia no Docker"
	@echo "  $(YELLOW)make docker-shell$(RESET)           → Abre shell dentro do container"
	@echo "  $(YELLOW)make docker-compose-up$(RESET)      → Inicia com docker-compose"
	@echo "  $(YELLOW)make docker-compose-down$(RESET)    → Para o docker-compose"
	@echo "  $(YELLOW)make docker-clean$(RESET)           → Remove imagens Docker"
	@echo ""
	@echo "$(GREEN)📦 O QUE CADA TARGET FAZ:$(RESET)"
	@echo "  $(BLUE)all$(RESET)           → Descompacta minilibx.tgz (se necessário),"
	@echo "                  compila Libft, MiniLibX e o fractol"
	@echo "  $(BLUE)clean$(RESET)         → Remove apenas arquivos .o"
	@echo "  $(BLUE)fclean$(RESET)        → Remove .o + executável"
	@echo "  $(BLUE)mlx-fclean$(RESET)    → Remove pasta minilibx-linux"
	@echo "  $(BLUE)re$(RESET)            → fclean + all (recompila tudo)"
	@echo ""
	@echo "$(GREEN)🎮 COMO USAR:$(RESET)"
	@echo "  $(YELLOW)./fractol mandelbrot$(RESET)           → Exibe fractal Mandelbrot"
	@echo "  $(YELLOW)./fractol julia [real] [imag]$(RESET)  → Exibe fractal Julia"
	@echo "  $(YELLOW)Exemplo:$(RESET) ./fractol julia -0.4 0.6"
	@echo ""
	@echo "$(GREEN)⌨️  CONTROLES NO PROGRAMA:$(RESET)"
	@echo "  $(YELLOW)ESC$(RESET)         → Fechar programa"
	@echo "  $(YELLOW)Setas$(RESET)       → Mover visualização"
	@echo "  $(YELLOW)+ / -$(RESET)       → Aumentar/diminuir iterações"
	@echo "  $(YELLOW)Mouse Scroll$(RESET) → Zoom in/out"
	@echo ""
	@echo "$(BLUE)╔═══════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║  Para mais informações: cat README.md                            ║$(RESET)"
	@echo "$(BLUE)╚═══════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""

.PHONY: all check-deps install-deps clean fclean mlx-fclean re help \
        docker-build docker-run-mandelbrot docker-run-julia \
        docker-shell docker-compose-up docker-compose-down docker-clean
