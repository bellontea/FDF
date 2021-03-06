/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_transforms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:24:42 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:48:03 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_isometric(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

void	ft_rotate_x(int *y, int *z, float alpha)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + *z * sin(alpha);
	*z = -prev_y * sin(alpha) + *z * cos(alpha);
}

void	ft_rotate_y(int *x, int *z, float beta)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(beta) + *z * sin(beta);
	*z = -prev_x * sin(beta) + *z * cos(beta);
}

void	ft_rotate_z(int *x, int *y, float gamma)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(gamma) - prev_y * sin(gamma);
	*y = prev_x * sin(gamma) + prev_y * cos(gamma);
}

t_dot	ft_update(t_fdf *fdf, t_dot dot)
{
	dot.x *= fdf->cam->zoom;
	dot.y *= fdf->cam->zoom;
	dot.z *= fdf->cam->zoom;
	dot.x -= (fdf->width * fdf->cam->zoom) / 2;
	dot.y -= (fdf->height * fdf->cam->zoom) / 2;
	ft_rotate_x(&(dot.y), &(dot.z), fdf->cam->alpha);
	ft_rotate_y(&(dot.x), &(dot.z), fdf->cam->beta);
	ft_rotate_z(&(dot.x), &(dot.y), fdf->cam->gamma);
	if (fdf->cam->projection == ISOMETRIC)
		ft_isometric(&(dot.x), &(dot.y), dot.z);
	dot.x += WIN_WIDTH / 2 + fdf->cam->shift_x;
	dot.y += WIN_HEIGHT / 2 + fdf->cam->shift_y;
	return (dot);
}
