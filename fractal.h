#ifndef FRACTAL_H
# define FRACTAL_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
//# include "minilibx_linux/mlx.h"

#define WIDTH 800
#define HEIGHT 800

typedef struct	s_image
{
	void	*img_ptr;
	char	*pxl_ptr;
	int		bits_per_pxl;
	int		endian;
	int		l_len;
}				t_image;


typedef struct s_fractal
{
	char	*name;
	void	*mlx_connction;
	void	*mlx_window;
	t_image	img;
}				t_fractal;


//Libft
////libft
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);

#endif