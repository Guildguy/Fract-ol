/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:15:10 by fleite-j          #+#    #+#             */
/*   Updated: 2025/04/18 20:15:12 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	error_handler(int c, char **v, double julia_x, double julia_y)
{
	if (c == 1 || !v[1])
		ft_putstr_fd("Please, type 'mandelbrot' \
or 'julia' set on command line!\n", STDERR_FILENO);
	else if (c != 2 && !ft_strncmp(v[1], "mandelbrot", 10))
		ft_putstr_fd("The 'mandelbrot' set does not require other \
arguments on command line!\n", STDERR_FILENO);
	else if (c != 4 && !ft_strncmp(v[1], "julia", 5))
		ft_putstr_fd("The 'julia' set requires <real> and <imaginary> \
values on command line!\n", STDERR_FILENO);
	else if (c == 4 && !ft_strncmp(v[1], "julia", 5)
		&& (julia_x == 0.0 || julia_y == 0.0))
		ft_putstr_fd("Invalid julia parameters: <real> and <imaginary> \
values need to be non-zero!\n", STDERR_FILENO);
	else if (c == 4 && !ft_strncmp(v[1], "julia", 5)
		&& (julia_x != 0.0 && julia_y != 0.0))
		return ;
	else
		ft_putstr_fd("Invalid argument: use 'mandelbrot' \
or 'julia <real> <imaginary>'\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
