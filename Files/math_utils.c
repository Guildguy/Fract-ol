/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:38:26 by fleite-j          #+#    #+#             */
/*   Updated: 2025/04/15 11:38:29 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include "minilibx-linux/mlx.h"

double	map(double unscaled_n, t_map_range range)
{
	return ((range.n_max - range.n_min) * (unscaled_n - range.o_min)
		/ (range.o_max - range.o_min) + range.n_min);
}

void	init_range_x(t_map_range *range)
{
	range->n_min = -2;
	range->n_max = +2;
	range->o_min = 0;
	range->o_max = WIDTH;
}

void	init_range_y(t_map_range *range)
{
	range->n_min = +2;
	range->n_max = -2;
	range->o_min = 0;
	range->o_max = HEIGHT;
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

t_complex	sqr_complex(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}
