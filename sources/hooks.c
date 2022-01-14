#include "fdf.h"

int	win_close_esc(int keycode, t_fdf *fdf)
{
	printf("%d\n", keycode);
	if (keycode == MAIN_PAD_ESC || keycode == 65307)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
//		mlx_destroy_image(vars->mlx, vars->img->img);
		exit(0);
	}
	return (0);
}

int win_close(int keycode, t_fdf *fdf)
{
//	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
//		mlx_destroy_image(vars->mlx, vars->img->img);
	exit(0);
}

void set_win_close(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, 2, 1L<<0, win_close_esc, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, win_close, fdf);
}