#include "../fractol.h"
#include "minilibx-linux/mlx.h"

double	map(double unscaled_n, double n_min,
			double n_max, double o_min, double o_max)
{
	return ((n_max - n_min) * (unscaled_n - o_min) / (o_max - o_min) + n_min);
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