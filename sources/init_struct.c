#include "fdf.h"

void ft_fill_line(char **coords_char, int **coords)
{
	int i;

	i = 0;
	while (coords_char[i])
	{
		(*coords)[i] = ft_atoi(coords_char[i]);
		i++;
	}
}

t_map *ft_init_map(int y, char **coords_char, int width)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
//    map->width = ft_size_arr(coords);
	map->coords = NULL;
	map->coords = ft_calloc(sizeof(int), width);
  //  map->line = malloc(sizeof(int) * map->width);
	ft_fill_line(coords_char, &(map->coords));
	map->y = y;
	map->next = NULL;
	return (map);
}

t_cam	*ft_init_cam()
{
	t_cam *cam;

	cam = malloc(sizeof(t_cam));
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
	cam->shift_x = WIN_WIDTH / 3;
	cam->shift_y = WIN_HEIGHT / 3;
	return (cam);
}

t_fdf *ft_init_fdf()
{
	t_fdf *fdf;
	fdf = malloc(sizeof(t_fdf));
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	fdf->img.img = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &(fdf->img.bits_per_pixel),
			&(fdf->img.line_length), &(fdf->img.endian));
	fdf->cam = ft_init_cam();
	set_win_close(fdf);
	return (fdf);
}

t_dot	ft_init_dot(int x, int y, int z)
{
	t_dot dot;

	dot.x = x;
	dot.y = y;
	dot.z = z;
	return (dot);
}