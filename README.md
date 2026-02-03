# Fractol

*This project was created as part of the 42 curriculum by fleite-j.*

## Description

Fract'ol is a computer graphics project that explores the beauty of fractals through interactive visualization. The program renders the famous **Mandelbrot** and **Julia** sets using pixel-by-pixel computation and complex number mathematics.

The project demonstrates fundamental concepts of computer graphics, including:
- Pixel manipulation and image rendering
- Complex number operations
- Color mapping and visual aesthetics
- Real-time user interaction (keyboard and mouse events)
- Mathematical visualization of iterative functions

Built using the **MiniLibX** graphics library, Fract'ol provides an intuitive interface for exploring fractals with smooth zooming, panning, and iteration control.

## Instructions

### Prerequisites

**For Local Compilation:**
- GCC compiler
- Make
- X11 development libraries
- MiniLibX dependencies

**For Docker (Recommended):**
- Docker installed
- X Server configured (for GUI display)

### Installation & Compilation

**Option 1: Local Compilation (Linux)**

1. Install system dependencies:
```bash
make install-deps
```

2. Compile the project:
```bash
make
```

3. Run the program:
```bash
./fractol mandelbrot
# or
./fractol julia <real> <imaginary>
```

**Option 2: Docker (Recommended)**

1. Build Docker image:
```bash
make docker-build
```

2. Run Mandelbrot set:
```bash
make docker-run-mandelbrot
```

3. Run Julia set:
```bash
make docker-run-julia
```

### Usage Examples

**Mandelbrot Set:**
```bash
./fractol mandelbrot
```

**Julia Set (requires real and imaginary parameters):**
```bash
./fractol julia -0.4 0.6
./fractol julia 0.285 0.01
./fractol julia -0.7 0.27015
```

**Valid Julia parameters:**
- Both values must be between -2.0 and 2.0
- At least one value must be non-zero

### Controls

| Key/Action | Function |
|------------|----------|
| `ESC` | Close the program |
| `Arrow Keys` | Pan the view |
| `+` / `-` | Increase/decrease iterations |
| `Mouse Scroll Up` | Zoom in (follows mouse position) |
| `Mouse Scroll Down` | Zoom out (follows mouse position) |

### Makefile Targets

| Command | Description |
|---------|-------------|
| `make` | Compile the entire project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and executable |
| `make re` | Recompile everything from scratch |
| `make install-deps` | Install system dependencies |
| `make docker-build` | Build Docker image |
| `make docker-run-mandelbrot` | Run Mandelbrot in Docker |
| `make docker-run-julia` | Run Julia in Docker |
| `make help` | Display detailed help menu |

## Features

### Core Features
- **Mandelbrot Set Rendering**: Classic fractal with infinite zoom capability
- **Julia Set Rendering**: Customizable parameters for different Julia set variations
- **Real-time Rendering**: Efficient pixel-by-pixel computation
- **Color Mapping**: Psychedelic color scheme based on iteration count

### Bonus Features
✅ **Mouse-position Based Zoom**: Zoom follows the exact mouse cursor position  
✅ **View Panning**: Navigate the fractal using arrow keys  
✅ **Dynamic Iteration Control**: Adjust detail level with +/- keys  
✅ **Docker Support**: Easy deployment with containerization

## Technical Details

### Project Structure
```
fractol/
├── srcs/              # Source files
│   ├── fractol.c      # Main entry point
│   ├── init.c         # Initialization functions
│   ├── render.c       # Fractal rendering logic
│   ├── events.c       # Event handlers (keyboard/mouse)
│   ├── math_utils.c   # Complex number operations
│   └── error_handler.c # Input validation
├── includes/          # Header files
│   └── fractol.h      # Main header
├── Libft/             # Custom C library
│   └── libft/         # Utility functions
├── docker-config/     # Docker configuration
└── Makefile           # Build automation
```

### Key Algorithms

**Mandelbrot Set Iteration:**
```
For each pixel (x, y):
  c = pixel_to_complex(x, y)
  z = 0
  while |z| < 2 and iterations < max:
    z = z² + c
    iterations++
  color = map_color(iterations)
```

**Julia Set Iteration:**
```
For each pixel (x, y):
  z = pixel_to_complex(x, y)
  c = julia_constant
  while |z| < 2 and iterations < max:
    z = z² + c
    iterations++
  color = map_color(iterations)
```

### Color Scheme
The project uses a custom psychedelic color palette defined in [`includes/fractol.h`](includes/fractol.h):
- MAGENTA_BURST (`0xFF00FF`)
- PSYCHEDELIC_PURPLE (`0x660066`)
- And additional colors for visual appeal

## Resources

### Classic References

**Fractal Mathematics:**
- [Mandelbrot Set - Wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set)
- [Julia Set - Wikipedia](https://en.wikipedia.org/wiki/Julia_set)
- *The Fractal Geometry of Nature* by Benoit Mandelbrot

**Graphics Programming:**
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [X11 Programming Manual](https://www.x.org/releases/current/doc/)

**Complex Numbers:**
- [Complex Number Operations](https://mathworld.wolfram.com/ComplexNumber.html)

### AI Usage

AI assistance was used for the following tasks:

1. **Code Structure Optimization**: Suggestions for organizing the codebase into modular functions ([`srcs/render.c`](srcs/render.c), [`srcs/math_utils.c`](srcs/math_utils.c))

2. **Docker Configuration**: Initial setup of [`docker-config/Dockerfile`](docker-config/Dockerfile) and [`docker-config/docker-compose.yml`](docker-config/docker-compose.yml)

3. **Makefile Improvements**: Enhanced [`Makefile`](Makefile) with color-coded output and dependency checking

4. **Error Handling Logic**: Input validation patterns in [`srcs/error_handler.c`](srcs/error_handler.c)

5. **Documentation**: README structure and formatting suggestions

**Parts of the project created with AI assistance:**
- Docker deployment scripts: [`docker-config/tools/install_dependencies.sh`](docker-config/tools/install_dependencies.sh), [`docker-config/tools/run_docker.sh`](docker-config/tools/run_docker.sh)
- Makefile help menu and automation
- README.md formatting and structure

**Core algorithms and fractal mathematics were implemented independently**, following mathematical definitions and 42 project requirements.

## Learning Outcomes

Through this project, I gained practical experience in:

- **Computer Graphics Fundamentals**: Understanding pixel buffers, image rendering, and efficient screen updates
- **Complex Number Mathematics**: Implementing mathematical operations and understanding their geometric interpretations
- **Event-Driven Programming**: Handling user input asynchronously with hooks
- **Memory Management**: Working with image buffers and managing graphical resources
- **MiniLibX Library**: Mastering a low-level graphics library for window management
- **Optimization Techniques**: Improving rendering performance for real-time interaction
- **Docker Deployment**: Containerizing graphical applications with X11 forwarding

## System Requirements

- **Linux**: Ubuntu 20.04+ / Debian 11+ / Fedora 35+ / Arch Linux
- **Windows**: WSL2 with X Server (VcXsrv, GWSL, or WSLg)
- **macOS**: Not officially supported (MiniLibX Linux version required)

## License

This project is part of the 42 school curriculum and follows the school's policies.

---

**Note**: For WSL2 users, ensure you have an X Server running (VcXsrv, GWSL, or use WSLg on Windows 11).