/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:38:40 by fleite-j          #+#    #+#             */
/*   Updated: 2025/04/15 11:38:43 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	pxl_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->l_len) + (x * (img->bits_per_pxl / 8));
	*(unsigned int *)(img->pxl_ptr + offset) = color;
}

static int	get_color(int iter, int max_iter)
{
	t_map_range	range_color;

	range_color.n_min = MAGENTA_BURST;
	range_color.n_max = PSYCHEDELIC_PURPLE;
	range_color.o_min = 0;
	range_color.o_max = max_iter;
	return ((int)map(iter, range_color));
}

static void	mandelbrot_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		z->x = z->x;
		z->y = z->y;
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
		z->x = 0.0;
		z->y = 0.0;
	}
}

static void	handle_pxl(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	t_map_range	range_x;
	t_map_range	range_y;
	int			i;

	i = 0;
	init_range_x(&range_x);
	init_range_y(&range_y);
	z.x = (map(x, range_x) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, range_y) * fractal->zoom) + fractal->shift_y;
	mandelbrot_vs_julia(&z, &c, fractal);
	while (i < fractal->iter_def)
	{
		z = sum_complex(sqr_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_val)
		{
			pxl_put(x, y, &fractal->img, get_color(i, fractal->iter_def));
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
