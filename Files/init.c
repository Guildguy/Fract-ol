#include "../fractal.h"

static void	malloc_error(void)
{
	perror("Problems w/ malloc");
	exit(EXIT_FAILURE);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connction = mlx_init();
	if (fractal->mlx_connction == NULL)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connction,
										WIDTH, HEIGHT, fractal->name);
	if (fractal->mlx_window == NULL)
	{
		mlx_destroy_display(fractal->mlx_connction);
		free(fractal->mlx_connction);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connction, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_connction, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connction);
		free(fractal->mlx_connction);
		malloc_error();
	}
	fractal->img.pxl_ptr = mlx_get_data_addr(fractal->img.img_ptr,
											&fractal->img.bits_per_pxl,
											&fractal->img.l_len,
											&fractal->img.endian);
	
}