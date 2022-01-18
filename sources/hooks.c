/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:52:33 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/18 20:40:50 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_win_close(t_fdf *fdf)
{
	t_map	*ptr;

	if (fdf == NULL)
		exit(0);
	if (fdf->img.img != NULL)
		mlx_destroy_image(fdf->mlx_ptr, fdf->img.img);
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->mlx_ptr)
		free(fdf->mlx_ptr);
	if (fdf->map != NULL)
	{
		while (fdf->map)
		{
			ptr = fdf->map->next;
			free(fdf->map->coords);
			free(fdf->map);
			fdf->map = ptr;
		}
	}
	if (fdf->cam)
		free(fdf->cam);
	if (fdf)
		free(fdf);
	exit(0);
}

int	rotate(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_A)
		fdf->cam->gamma += 0.1;
	else if (keycode == KEY_D)
		fdf->cam->gamma -= 0.1;
	else if (keycode == KEY_S)
		fdf->cam->alpha += 0.1;
	else if (keycode == KEY_W)
		fdf->cam->alpha -= 0.1;
	else if (keycode == KEY_Q)
		fdf->cam->beta += 0.1;
	else if (keycode == KEY_E)
		fdf->cam->beta -= 0.1;
	ft_draw_map(fdf);
	return (0);
}

int	shift(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_UP)
		fdf->cam->shift_y -= 10;
	else if (keycode == KEY_DOWN)
		fdf->cam->shift_y += 10;
	else if (keycode == KEY_LEFT)
		fdf->cam->shift_x -= 10;
	else if (keycode == KEY_RIGHT)
		fdf->cam->shift_x += 10;
	ft_draw_map(fdf);
	return (0);
}

void	ft_mouse_zoom(int keycode, t_fdf *fdf)
{
	if (fdf->cam->zoom < 10000 && keycode == KEY_PLUS)
		fdf->cam->zoom += 5;
	else if (fdf->cam->zoom >= 5 && keycode == KEY_MINUS)
		fdf->cam->zoom -= 5;
	else
		return ;
	ft_draw_map(fdf);
}

void	change_proection(int keycode, t_fdf *fdf)
{
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	if (keycode == KEY_X || keycode == 120)
		fdf->cam->projection = PARALLEL;
	else if (keycode == KEY_Z || keycode == 122)
		fdf->cam->projection = ISOMETRIC;
	ft_draw_map(fdf);
}

int	ft_key_hooks(int keycode, t_fdf *fdf)
{
	printf("%d\n", keycode);
	if (keycode == KEY_ESC)
		ft_win_close(fdf);
	else if (keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
		shift(keycode, fdf);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		ft_mouse_zoom(keycode, fdf);
	else if (keycode == KEY_A || keycode == KEY_D
		|| keycode == KEY_S || keycode == KEY_W
		|| keycode == KEY_Q || keycode == KEY_E)
		rotate(keycode, fdf);
	else if (keycode == KEY_Z || keycode == KEY_X)
		change_proection(keycode, fdf);
	return (0);
}
