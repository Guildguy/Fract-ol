#include "../fractol.h"
#include "minilibx-linux/mlx.h"

int	main(int c, char **v)
{
	t_fractal	fractal;
	if ((c == 2 && !ft_strncmp(v[1], "mandelbrot", 10))
		|| (c == 4 && !ft_strncmp(v[1], "julia", 5)))
	{
		fractal.name = v[1];
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		ft_putstr_fd("ERROR!", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}