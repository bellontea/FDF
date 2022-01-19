/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:44:03 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:46:52 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_key_hooks(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		ft_win_close(fdf);
	else if (keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
		ft_shift(keycode, fdf);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		ft_mouse_zoom(keycode, fdf);
	else if (keycode == KEY_A || keycode == KEY_D
		|| keycode == KEY_S || keycode == KEY_W
		|| keycode == KEY_Q || keycode == KEY_E)
		ft_rotate(keycode, fdf);
	else if (keycode == KEY_Z || keycode == KEY_X)
		ft_change_proection(keycode, fdf);
	return (0);
}
