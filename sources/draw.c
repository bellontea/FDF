#include "fdf.h"

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

int ft_abs(int num)
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

void ft_draw_line(t_dot dot1, t_dot dot2, t_fdf *fdf)
{
	int step_x;
	int step_y;
	float s_x;
	float s_y;
	int max;
	int color;
	t_dot dot1_save;

	dot1_save = dot1;
	 
//	printf("beforex = %d, y = %d, x1 = %d, y1 = %d\n", dot1.x, dot1.y, dot2.x, dot2.y);	 
	//  dot1.x *= fdf->cam->zoom;
	//  dot1.y *= fdf->cam->zoom;
	//  dot2.x *= fdf->cam->zoom;
	//  dot2.y *= fdf->cam->zoom;
	//  dot1.z *= fdf->cam->zoom;
	//  dot2.z *= fdf->cam->zoom;
	// isometric(&(dot1.x), &(dot1.y), dot1.z);
	// isometric(&(dot2.x), &(dot2.y), dot2.z);

//	printf("x = %d, y = %d, x1 = %d, y1 = %d\n", dot1.x, dot1.y, dot2.x, dot2.y);
//	isometric(&x, &y, z);
//	isometric(&x1, &y1, z1);

	//  dot1.x += fdf->cam->shift_x;
	//  dot1.y += fdf->cam->shift_y;
	//  dot2.x += fdf->cam->shift_x;
	//  dot2.y += fdf->cam->shift_y;


	step_x = dot2.x - dot1.x;
	step_y = dot2.y - dot1.y;
	max = MAX(ft_abs(step_x), ft_abs(step_y));
	if (max)
	{
	s_x = (float)step_x / (float)max;
	s_y = (float)step_y / (float)max;

	}
	// else
	// {
	// 	step_x = 0;
	// 	step_y = 0;
	// }
//	printf("COORDS x = %d, y = %d, x1 = %d, y1 = %d\n", dot1.x, dot1.y, dot2.x, dot2.y);
	int i = 0;
	int save_x = dot1.x;
	int save_y = dot1.y;
	float save_s_x = s_x;
	float save_s_y = s_y;
//	printf("BEGIN s_x = %f, s_y = %f\n", save_s_x, save_s_y);
	while ((dot1.x != dot2.x) || (dot1.y != dot2.y))
	{
//		printf("*");
		color = get_color(ft_init_dot(dot1.x, dot1.y, dot1_save.z, fdf), dot1_save, dot2, ft_abs(step_x), ft_abs(step_y));
//		color = COLOR_1;
		my_mlx_pixel_put(fdf->img, dot1.x, dot1.y, color);
//		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xffffff);
		if (i != 0)
		{
			s_x += save_s_x;
			s_y += save_s_y;
		}
		if (dot1.x != dot2.x)
			dot1.x = save_x + (int)s_x;
		if (dot1.y != dot2.y)
			dot1.y = save_y + (int)s_y;
//		printf("x = %d, y = %d, s_x = %f, s_y = %f\n", dot1.x, dot1.y, s_x, s_y);
		 if ((dot1.x > WIN_WIDTH) || (dot1.y > WIN_HEIGHT))
		 	break ;
		i++;
	}

}

void refresh_win(t_fdf *fdf)
{
	int	i;
	int	*image;

	i = 0;
	image = (int *)fdf->img.addr;
	while (i < WIN_HEIGHT * WIN_WIDTH)
	{
		image[i] = 0x000000;
		i++;
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
	refresh_win(fdf);
	while (y < fdf->height)
	{
		while (x < fdf->width)
		{
			if (x != fdf->width - 1)
				ft_draw_line(ft_update(fdf, ft_init_dot(x, y, curr_y->coords[x], fdf)), 
				ft_update(fdf, ft_init_dot(x + 1, y, curr_y->coords[x + 1], fdf)), fdf);
//				ft_draw_line(x, y, curr_y->coords[x], x + 1, y, curr_y->coords[x + 1], fdf);
			if (y != fdf->height - 1)
				ft_draw_line(ft_update(fdf, ft_init_dot(x, y, curr_y->coords[x], fdf)), 
				ft_update(fdf, ft_init_dot(x, y + 1, next_y->coords[x], fdf)), fdf);
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