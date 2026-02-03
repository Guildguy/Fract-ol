#!/bin/bash

# Script para instalar dependências do Fractol

# Cores para output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${BLUE}🔍 Detectando sistema operacional...${NC}"

if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
else
    echo -e "${RED}❌ Não foi possível detectar o sistema operacional${NC}"
    exit 1
fi

echo -e "${BLUE}📦 Instalando dependências para $OS...${NC}"

case $OS in
    ubuntu|debian|pop)
        echo -e "${BLUE}🔧 Instalando dependências para Ubuntu/Debian...${NC}"
        sudo apt-get update
        sudo apt-get install -y \
            build-essential \
            gcc \
            make \
            libx11-dev \
            libxext-dev \
            libbsd-dev \
            libxcb1-dev \
            xorg \
            pkg-config
        ;;
    
    fedora|rhel|centos)
        echo -e "${BLUE}🔧 Instalando dependências para Fedora/RHEL...${NC}"
        sudo dnf install -y \
            gcc \
            make \
            libX11-devel \
            libXext-devel \
            libbsd-devel \
            pkg-config
        ;;
    
    arch|manjaro)
        echo -e "${BLUE}🔧 Instalando dependências para Arch/Manjaro...${NC}"
        sudo pacman -S --needed --noconfirm \
            gcc \
            make \
            libx11 \
            libxext \
            libbsd \
            pkg-config
        ;;
    
    *)
        echo -e "${RED}❌ Sistema operacional não suportado: $OS${NC}"
        echo ""
        echo "Instale manualmente as seguintes dependências:"
        echo "  - gcc"
        echo "  - make"
        echo "  - libx11-dev (ou libX11-devel)"
        echo "  - libxext-dev (ou libXext-devel)"
        echo "  - libbsd-dev (ou libbsd-devel)"
        echo "  - pkg-config"
        exit 1
        ;;
esac

echo ""
echo -e "${GREEN}✅ Dependências instaladas com sucesso!${NC}"
echo ""
echo -e "${YELLOW}Agora você pode compilar o projeto com:${NC}"
echo -e "  ${GREEN}make${NC}"
