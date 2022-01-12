#include "fdf.h"

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

float ft_abs(float num)
{
	if (num < 0)
		num = -num;
	return (num);
}

void isometric(float *x, float *y, float z)
{
	*x = (*x - *y) * cos(0.523599);
	*y = (*x + *y) * sin(0.523599) - z;
}

void ft_draw_line(float x, float y, float z, float x1, float y1, float z1, t_fdf *fdf)
{
	float step_x;
	float step_y;
	float max;

	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);

	x *= fdf->zoom;
	y *= fdf->zoom;
	x1 *= fdf->zoom;
	y1 *= fdf->zoom;

	x += 300;
	y += 300;
	x1 += 300;
	y1 += 300;

	step_x = x1 - x;
	step_y = y1 - y;
	max = MAX(ft_abs(step_x), ft_abs(step_y));
	step_x /= max;
	step_y /= max;

	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xffffff);
		x += step_x;
		y += step_y;
	}

}

void ft_draw_map(t_fdf *fdf)
{
	t_map *save;
	t_map *curr_y;
	t_map *next_y;
	int y;
	int x;

	save = fdf->map;
	curr_y = fdf->map;
	next_y = fdf->map->next;
	y = 0;
	x = 0;

	//printf("%d, %d\n", fdf->height, fdf->width);
	while (y < fdf->height)
	{
		while (x < fdf->width)
		{
			if (x != fdf->width - 1)
				ft_draw_line(x, y, curr_y->coords[x], x + 1, y, curr_y->coords[x + 1], fdf);
			if (y != fdf->height - 1)
				ft_draw_line(x, y, curr_y->coords[x], x, y + 1, next_y->coords[x], fdf);
		//	printf("%d - %d\n", i, j);
			x++;
		}
		y++;
		curr_y = next_y;
		if (curr_y)
			next_y= curr_y->next;
		x = 0;
	}
}