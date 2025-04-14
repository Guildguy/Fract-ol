#include "../fractol.h"
#include "minilibx-linux/mlx.h"

static void	pxl_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->l_len) + (x * (img->bits_per_pxl / 8));
	*(unsigned int *)(img->pxl_ptr + offset) = color;
}

static void	handle_pxl(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = map(x, -2, +2, 0, WIDTH);
	c.y = map(y, +2, -2, 0, HEIGHT);
	while (i < fractal->iter_def)
	{
		z = sum_complex(sqr_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_val)
		{
			color = map(i, WHITE, BLACK, 0, fractal->iter_def);
			pxl_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	pxl_put(x, y, &fractal->img, BLACK);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pxl(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection,
							fractal->mlx_window,
							fractal->img.img_ptr,
							0, 0);
}
