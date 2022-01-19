/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:25:06 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 19:02:27 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*c;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		c = img.addr + (y * img.line_length) + (x * img.bits_per_pixel / 8);
		*(unsigned int *)c = color;
	}
}

void	ft_draw_line(t_dot start, t_dot end, t_fdf *fdf)
{
	t_dot	current;
	t_dot	delta;
	t_steps	steps;
	double	x;
	double	y;

	current = start;
	x = (double)current.x;
	y = (double)current.y;
	delta.x = ft_abs(end.x - start.x);
	delta.y = ft_abs(end.y - start.y);
	steps.x = (double)(end.x - start.x) / (double)ft_max(delta.x, delta.y);
	steps.y = (double)(end.y - start.y) / (double)ft_max(delta.x, delta.y);
	while ((int)(end.x - x) || (int)(end.y - y))
	{
		my_mlx_pixel_put(fdf->img, current.x, current.y,
			get_color(current, start, end, delta));
		x += steps.x;
		y += steps.y;
		current.x = (int)x;
		current.y = (int)y;
		if ((start.x > WIN_WIDTH && end.x > WIN_WIDTH)
			|| (start.y > WIN_HEIGHT && end.y > WIN_HEIGHT))
			break ;
	}
}

void	ft_draw_background(t_fdf *fdf)
{
	int	i;
	int	*image;

	i = 0;
	image = (int *)fdf->img.addr;
	while (i < WIN_HEIGHT * WIN_WIDTH)
	{
		image[i] = BACKGROUND;
		i++;
	}
}

void	ft_draw_x(t_fdf *fdf, t_map *curr_y, t_map *next_y, int y)
{
	int	x;

	x = 0;
	while (x < fdf->width)
	{
		if (x != fdf->width - 1)
			ft_draw_line(ft_update(fdf, ft_init_dot(x, y, curr_y->coords[x],
						fdf)), ft_update(fdf, ft_init_dot(x + 1, y,
						curr_y->coords[x + 1], fdf)), fdf);
		if (y != fdf->height - 1)
			ft_draw_line(ft_update(fdf, ft_init_dot(x, y, curr_y->coords[x],
						fdf)), ft_update(fdf, ft_init_dot(x, y + 1,
						next_y->coords[x], fdf)), fdf);
		x++;
	}
}

void	ft_draw_map(t_fdf *fdf)
{
	t_map	*curr_y;
	t_map	*next_y;
	int		y;

	y = 0;
	curr_y = fdf->map;
	next_y = fdf->map->next;
	ft_draw_background(fdf);
	while (y < fdf->height)
	{
		ft_draw_x(fdf, curr_y, next_y, y);
		curr_y = next_y;
		if (curr_y)
			next_y = curr_y->next;
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img, 0, 0);
}
