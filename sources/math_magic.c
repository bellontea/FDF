#include "fdf.h"

void isometric(int *x, int *y, int z)
{
	int prev_x;
	int prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

void	rotate_x(int *y, int *z, float alpha)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + *z * sin(alpha);
	*z = -prev_y * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(int *x, int *z, float beta)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(beta) + *z * sin(beta);
	*z = -prev_x * sin(beta) + *z * cos(beta);
}

void	rotate_z(int *x, int *y, float gamma)
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
//	printf("before x = %d, y = %d, z = %d\n", dot.x, dot.y, dot.z);
	rotate_x(&(dot.y), &(dot.z), fdf->cam->alpha);
	rotate_y(&(dot.x), &(dot.z), fdf->cam->beta);
	rotate_z(&(dot.x), &(dot.y), fdf->cam->gamma);
	if (fdf->cam->projection == ISOMETRIC)
		isometric(&(dot.x), &(dot.y), dot.z);
	dot.x += WIN_WIDTH / 2 + fdf->cam->shift_x;
	dot.y += WIN_HEIGHT / 2 + fdf->cam->shift_y;
//	printf("x = %d, y = %d, z = %d\n", dot.x, dot.y, dot.z);
	return (dot);
}