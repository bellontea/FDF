/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:45:14 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/18 20:33:09 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_fill_line(t_map *map, char **coords_char, int **coords)
{
	int	i;

	i = 0;
	while (coords_char[i])
	{
		(*coords)[i] = ft_atoi(coords_char[i]);
		if (map->z_min > (*coords)[i])
			map->z_min = (*coords)[i];
		if (map->z_max < (*coords)[i])
			map->z_max = (*coords)[i];
		i++;
	}
}

t_map	*ft_init_map(int y, char **coords_char, int width)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->coords = NULL;
	map->coords = ft_calloc(sizeof(int), width);
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	ft_fill_line(map, coords_char, &(map->coords));
	map->y = y;
	map->next = NULL;
	ft_free_array(coords_char);
	return (map);
}

t_cam	*ft_init_cam(void)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (cam == NULL)
		return (cam);
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
	cam->shift_x = 0;
	cam->shift_y = 0;
	cam->prev_shift_x = cam->shift_x;
	cam->prev_shift_y = cam->shift_y;
	cam->projection = ISOMETRIC;
	return (cam);
}

t_fdf	*ft_fdf_malloc(void)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (fdf == NULL)
		return (NULL);
	fdf->cam = NULL;
	fdf->map = NULL;
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	return (fdf);
}

t_fdf	*ft_init_fdf(void)
{
	t_fdf	*fdf;

	fdf = ft_fdf_malloc();
	if (fdf == NULL)
		return (NULL);
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		return (NULL);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (fdf->win_ptr == NULL)
		return (NULL);
	fdf->img.img = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (fdf->img.img == NULL)
		return (NULL);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &(fdf->img.bits_per_pixel),
			&(fdf->img.line_length), &(fdf->img.endian));
	fdf->cam = ft_init_cam();
	if (fdf->cam == NULL)
		return (NULL);
	fdf->z_min = INT_MAX;
	fdf->z_max = INT_MIN;
	mlx_hook(fdf->win_ptr, 2, 1L << 0, ft_key_hooks, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, ft_win_close, fdf);
	return (fdf);
}

t_dot	ft_init_dot(int x, int y, int z, t_fdf *fdf)
{
	t_dot	dot;

	dot.x = x;
	dot.y = y;
	dot.z = z;
	dot.color = get_default_color(z, fdf);
	return (dot);
}
