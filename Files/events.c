/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:13:09 by fleite-j          #+#    #+#             */
/*   Updated: 2025/04/16 23:13:11 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	close_handler(t_fractal *fractal)
{	
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	if (keysym == XK_Left)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y -= (0.5 * fractal->zoom);
	if (keysym == XK_plus)
		fractal->iter_def -= 10;
	else if (keysym == XK_minus)
		fractal->iter_def += 10;
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	double		mouse_x;
	double		mouse_y;
	t_map_range	range_x;
	t_map_range	range_y;

	init_range_x(&range_x);
	init_range_y(&range_y);
	mouse_x = map(x, range_x) * fractal->zoom + fractal->shift_x;
	mouse_y = map(y, range_y) * fractal->zoom + fractal->shift_y;
	if (button == Button4 && fractal->zoom > 0.000001)
	{
		fractal->zoom *= 0.8;
		fractal->shift_x += (mouse_x - fractal->shift_x) * 0.3;
		fractal->shift_y += (mouse_y - fractal->shift_y) * 0.3;
	}
	else if (button == Button5 && fractal->zoom < 1000.0)
	{
		fractal->zoom *= 1.2;
		fractal->shift_x += (mouse_x - fractal->shift_x) * -0.2;
		fractal->shift_y += (mouse_y - fractal->shift_y) * -0.2;
	}
	fractal_render(fractal);
	return (0);
}
