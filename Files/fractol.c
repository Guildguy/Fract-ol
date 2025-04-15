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
