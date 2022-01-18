/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:25:06 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/18 21:27:55 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

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

	current = start;
	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	steps.x = (double)delta.x / (double)ft_max(abs(delta.x), abs(delta.y));
	steps.y = (double)delta.y / (double)ft_max(abs(delta.x), abs(delta.y));
	steps.sum_x = steps.x;
	steps.sum_y = steps.y;
	while ((current.x != end.x) || (current.y != end.y))
	{
		my_mlx_pixel_put(fdf->img, current.x, current.y,
			get_color(current, start, end, delta));
		if (current.x != end.x)
			current.x = start.x + (int)steps.sum_x;
		if (current.y != end.y)
			current.y = start.y + (int)steps.sum_y;
		steps.sum_x += steps.x;
		steps.sum_y += steps.y;
		if ((start.x > WIN_WIDTH && end.x > WIN_WIDTH)
			|| (start.y > WIN_HEIGHT && end.y > WIN_HEIGHT))
			break ;
	}
}

void	refresh_win(t_fdf *fdf)
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

void	ft_draw_map(t_fdf *fdf)
{
	t_map	*curr_y;
	t_map	*next_y;
	int		y;
	int		x;

	curr_y = fdf->map;
	next_y = fdf->map->next;
	y = 0;
	x = 0;
	refresh_win(fdf);
	while (y < fdf->height)
	{
		while (x < fdf->width)
		{
			if (x != fdf->width - 1)
				ft_draw_line(ft_update(fdf, ft_init_dot(x, y, curr_y->coords[x], fdf)), ft_update(fdf, ft_init_dot(x + 1, y, curr_y->coords[x + 1], fdf)), fdf);
			if (y != fdf->height - 1)
				ft_draw_line(ft_update(fdf, ft_init_dot(x, y, curr_y->coords[x], fdf)), 
				ft_update(fdf, ft_init_dot(x, y + 1, next_y->coords[x], fdf)), fdf);
			x++;
		}
		y++;
		curr_y = next_y;
		if (curr_y)
			next_y = curr_y->next;
		x = 0;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img, 0, 0);
}
