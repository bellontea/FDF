#include "fdf.h"

void	win_close_esc(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
//	mlx_destroy_image(vars->mlx, vars->img->img);
	exit(0);
}
int win_close(int keycode, t_fdf *fdf)
{
//	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
//		mlx_destroy_image(vars->mlx, vars->img->img);
	exit(0);
}

int rotate(int keycode, t_fdf *fdf)
{
	printf("%d\n", keycode);
	if (keycode == MAIN_PAD_A || keycode == 97)
		fdf->cam->gamma += 0.1;
	else if (keycode == MAIN_PAD_D || keycode == 100)
		fdf->cam->gamma -= 0.1;
	else if (keycode == MAIN_PAD_S || keycode == 115)
		fdf->cam->alpha += 0.1;
	else if (keycode == MAIN_PAD_W || keycode == 119)
		fdf->cam->alpha -= 0.1;
	else if (keycode == MAIN_PAD_Q || keycode == 113)
		fdf->cam->beta += 0.1;
	else if (keycode == MAIN_PAD_E || keycode == 101)
		fdf->cam->beta -= 0.1;
	ft_draw_map(fdf);
	return (0);
}

int shift(int keycode, t_fdf *fdf)
{
	printf("%d\n", keycode);
	if (keycode == NUM_PAD_UP || keycode == 65362)
		fdf->cam->shift_y -= 50;
	else if (keycode == NUM_PAD_DOWN || keycode == 65364)
		fdf->cam->shift_y += 50;
	else if (keycode == NUM_PAD_LEFT || keycode == 65361)
		fdf->cam->shift_x -= 50;
	else if (keycode == NUM_PAD_RIGHT || keycode == 65363)
		fdf->cam->shift_x += 50;
	ft_draw_map(fdf);
	return (0);
}

int mouse_zoom(int button, int x, int y, t_fdf *fdf)
{
	printf("%d\n", fdf->cam->zoom);
	if (fdf->cam->zoom < 4096 && button == 4)
	{
		fdf->cam->zoom *= 2;
		fdf->cam->prev_shift_x = fdf->cam->shift_x;
		fdf->cam->prev_shift_y = fdf->cam->shift_y;
		fdf->cam->shift_x += (fdf->cam->shift_x - x);
		fdf->cam->shift_y += (fdf->cam->shift_y - y);
	}
	else if (fdf->cam->zoom != 1 && button == 5)
	{
		fdf->cam->zoom /= 2;
		fdf->cam->shift_x = fdf->cam->prev_shift_x;
		fdf->cam->shift_y = fdf->cam->prev_shift_y;
	}
	else
		return (0);
	ft_draw_map(fdf);
	return (0);
}

void change_proection(int keycode, t_fdf *fdf)
{
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	if (keycode == MAIN_PAD_X || keycode == 120)
		fdf->cam->projection = PARALLEL;
	else if (keycode == MAIN_PAD_Z || keycode == 122)
		fdf->cam->projection = ISOMETRIC;
	ft_draw_map(fdf);
}

int key_hooks(int keycode, t_fdf *fdf)
{
	printf("%d\n", keycode);
	if (keycode == MAIN_PAD_ESC || keycode == 65307)
		win_close_esc(fdf);
	else if (keycode == NUM_PAD_UP || keycode == 65362 ||
	keycode == NUM_PAD_DOWN || keycode == 65364 ||
	keycode == NUM_PAD_LEFT || keycode == 65361 ||
	keycode == NUM_PAD_RIGHT || keycode == 65363)
		shift(keycode, fdf);
	else if (keycode == MAIN_PAD_A || keycode == 97 ||
	keycode == MAIN_PAD_D || keycode == 100 ||
	keycode == MAIN_PAD_S || keycode == 115 ||
	keycode == MAIN_PAD_W || keycode == 119 ||
	keycode == MAIN_PAD_Q || keycode == 113 ||
	keycode == MAIN_PAD_E || keycode == 101)
		rotate(keycode, fdf);
	else if (keycode == MAIN_PAD_Z || keycode == 122 ||
	keycode == MAIN_PAD_X || keycode == 120)
		change_proection(keycode, fdf);
	return (0);
}

void set_win_close(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, 2, 1L<<0, key_hooks, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, win_close, fdf);
	mlx_mouse_hook(fdf->win_ptr, mouse_zoom, fdf);
}