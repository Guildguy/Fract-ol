FROM ubuntu:22.04

# Evitar prompts interativos durante a instalação
ENV DEBIAN_FRONTEND=noninteractive

# Instalar dependências do sistema
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    make \
    libx11-dev \
    libxext-dev \
    libbsd-dev \
    x11-apps \
    xauth \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Criar diretório de trabalho
WORKDIR /app

# Copiar arquivos do projeto
COPY . .

# Descompactar e compilar MiniLibX
RUN if [ -f minilibx-linux.tgz ]; then \
        tar -xzf minilibx-linux.tgz; \
    fi && \
    if [ -d minilibx-linux ]; then \
        cd minilibx-linux && make; \
    fi

# Compilar Libft
RUN make -C Libft

# Compilar o projeto
RUN make

# Comando padrão
CMD ["./fractol", "mandelbrot"]
	@echo "  - WSL2"
	@echo "  - X Server (VcXsrv, GWSL or WSLg)"
	@echo ""
