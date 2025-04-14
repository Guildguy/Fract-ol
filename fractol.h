/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:51:03 by fleite-j          #+#    #+#             */
/*   Updated: 2025/04/07 18:53:00 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"

# define WIDTH 800
# define HEIGHT 800

# define BLACK       0x000000
# define WHITE       0xFFFFFF
# define RED         0xFF0000
# define GREEN       0x00FF00
# define BLUE        0x0000FF
# define MAGENTA_BURST   0xFF00FF
# define LIME_SHOCK      0xCCFF00
# define NEON_ORANGE     0xFF6600
# define PSYCHEDELIC_PURPLE 0x660066
# define AQUA_DREAM      0x33CCCC
# define HOT_PINK        0xFF66B2
# define ELECTRIC_BLUE   0x0066FF
# define LAVA_RED        0xFF3300

typedef struct s_complex
{
	double	x;
	double	y;
}				t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pxl_ptr;
	int		bits_per_pxl;
	int		endian;
	int		l_len;
}				t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	double	escape_val;
	int		iter_def;
}				t_fractal;

//Libft
////libft
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);
//Files
////init
void		fractal_init(t_fractal *fractal);
//math_utils
double		map(double unscaled_n, double n_min, double n_max, double o_min, double o_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	sqr_complex(t_complex z);
////render
void		fractal_render(t_fractal *fractal);

#endif
