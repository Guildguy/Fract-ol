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

#include "../includes/fractol.h"

static bool	check_args(char *arg)
{
	int		len;
	bool	is_dot;
	bool	is_digit;

	len = 0;
	is_dot = false;
	is_digit = false;
	if (*arg == '-' || *arg == '+')
		arg++;
	else if (!(*arg >= '0' && *arg <= '9'))
		return (false);
	while (*arg)
	{
		if (*arg >= '0' && *arg <= '9')
			is_digit = true;
		else if (*arg == '.' && !is_dot)
			is_dot = true;
		arg++;
		len++;
		if (len > 20)
			return (false);
	}
	return (is_digit);
}

void	error_handler(int c, char **v, double julia_x, double julia_y)
{
	if (c == 1 || !v[1])
		ft_putstr_fd("Invalid parameters: use 'mandelbrot' \
or 'julia <real> <imaginary>' set on command line!\n", STDERR_FILENO);
	else if (c != 2 && !ft_strncmp(v[1], "mandelbrot", 10))
		ft_putstr_fd("Invalid parameters: 'mandelbrot' set does not require \
other arguments on command line!\n", STDERR_FILENO);
	else if (c != 4 && !ft_strncmp(v[1], "julia", 5))
		ft_putstr_fd("Invalid parameters: 'julia' set requires <real> and <imaginary> \
values on command line!\n", STDERR_FILENO);
	else if (c == 4 && !ft_strncmp(v[1], "julia", 5))
	{
		if (!check_args(v[2]) || !check_args(v[3]))
			ft_putstr_fd("Invalid julia parameters: <real> and <imaginary> \
values need to be numbers!\n", STDERR_FILENO);
		else if (julia_x == 0.0 && julia_y == 0.0)
			ft_putstr_fd("Invalid julia parameters: at least one value <real> or <imaginary> \
need to be non-zero!\n", STDERR_FILENO);
		else if (julia_x < -2.0 || julia_x > 2.0
			|| julia_y < -2.0 || julia_y > 2.0)
			ft_putstr_fd("Invalid julia parameters: <real> and <imaginary> must be \
at interval of -2.0 and 2.0\n", STDERR_FILENO);
		else
			return ;
	}
	else
		ft_putstr_fd("Invalid argument: use 'mandelbrot' \
or 'julia <real> <imaginary>'\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
