/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:13:40 by fleite-j          #+#    #+#             */
/*   Updated: 2025/04/16 23:13:41 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static void	atodbl_init(int	*sign, long *int_part,
						double *frac_part, double *pow)
{
	*sign = 1;
	*int_part = 0;
	*frac_part = 0.0;
	*pow = 1.0;
}

double	ft_atodbl(char *s)
{
	int		sign;
	long	int_part;
	double	frac_part;
	double	pow;

	atodbl_init(&sign, &int_part, &frac_part, &pow);
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
	int_part = int_part * 10 + (*s++ - '0');
	if (*s == '.')
	{
		s++;
		while (ft_isdigit(*s))
		{
			pow /= 10;
			frac_part += (*s++ - '0') * pow;
		}
	}
	return (sign * (int_part + frac_part));
}
