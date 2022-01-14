#include "fdf.h"

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

float ft_abs(float num)
{
	if (num < 0)
		num = -num;
	return (num);
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

// void isometric(float *x, float *y, float z)
// {
// 	int prev_x;
// 	int prev_y;

// 	prev_x = *x;
// 	prev_y = *y;
// 	*x = (prev_x - prev_y) * cos(0.523599);
// 	*y = (prev_x + prev_y) * sin(0.523599) - z;
// }

void ft_draw_line(t_dot dot1, t_dot dot2, t_fdf *fdf)
{
	float step_x;
	float step_y;
	float max;

	// isometric(&(dot1.x), &(dot1.y), dot1.z);
	// isometric(&(dot2.x), &(dot2.y), dot2.z);

	// dot1.x *= fdf->zoom;
	// dot1.y *= fdf->zoom;
	// dot2.x *= fdf->zoom;
	// dot2.y *= fdf->zoom;

//	isometric(&x, &y, z);
//	isometric(&x1, &y1, z1);

	// dot1.x += fdf->shift_x;
	// dot1.y += fdf->shift_y;
	// dot2.x += fdf->shift_x;
	// dot2.y += fdf->shift_y;

	step_x = dot2.x - dot1.x;
	step_y = dot2.y - dot1.y;
	max = MAX(ft_abs(step_x), ft_abs(step_y));
	step_x /= max;
	step_y /= max;

	while ((int)(dot1.x - dot2.x) || (int)(dot1.y - dot2.y))
	{
		printf("*");
		my_mlx_pixel_put(fdf->img, dot1.x, dot1.y, 0xffffff);
//		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xffffff);
		dot1.x += step_x;
		dot1.y += step_y;
		if ((dot1.x > WIN_WIDTH) || (dot1.x < 0) || (dot1.y > WIN_HEIGHT) || (dot1.y < 0))
			break ;
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
				ft_draw_line(ft_update(fdf, ft_init_dot(x, y, curr_y->coords[x])), 
				ft_update(fdf, ft_init_dot(x + 1, y, curr_y->coords[x + 1])), fdf);
//				ft_draw_line(x, y, curr_y->coords[x], x + 1, y, curr_y->coords[x + 1], fdf);
			if (y != fdf->height - 1)
				ft_draw_line(ft_update(fdf, ft_init_dot(x, y, curr_y->coords[x])), 
				ft_update(fdf, ft_init_dot(x, y + 1, next_y->coords[x])), fdf);
//				ft_draw_line(x, y, curr_y->coords[x], x, y + 1, next_y->coords[x], fdf);
		//	printf("%d - %d\n", i, j);
			x++;
		}
		y++;
		curr_y = next_y;
		if (curr_y)
			next_y= curr_y->next;
		x = 0;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img, 0, 0);
}