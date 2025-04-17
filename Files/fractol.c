/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:37:57 by fleite-j          #+#    #+#             */
/*   Updated: 2025/04/15 11:37:59 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	main(int c, char **v)
{
	t_fractal	fractal;

	if ((c == 2 && !ft_strncmp(v[1], "mandelbrot", 10))
		|| (c == 4 && !ft_strncmp(v[1], "julia", 5)))
	{
		fractal.name = v[1];
		fractal.julia_x = 0.0;
		fractal.julia_y = 0.0;
		if (c == 4 && !ft_strncmp(v[1], "julia", 5))
		{
			fractal.julia_x = ft_atodbl(v[2]);
			fractal.julia_y = ft_atodbl(v[3]);
			if (fractal.julia_x == 0.0 && fractal.julia_y == 0.0)
				exit(EXIT_FAILURE);
		}
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
