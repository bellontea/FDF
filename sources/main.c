#include "fdf.h"

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	main(int argc, char **argv)
{
	t_fdf *fdf;
	int fd;
	t_map *map;

	if (argc != 2)
	{
		printf("Error: too many or no arguments\n");
		return (1);
	}

	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		perror("Error");
		return (1);
	}
	fdf = ft_init_fdf();
	ft_read_map(fd, fdf);
	close(fd);
//	map = fdf.map;
	// while(map)
	// {
	// 	for(int i = 0; i < fdf.width; i++)
	// 		printf("%3d", map->coords[i]);
	// 	map = map->next;
	// 	printf("\n");
	// }

	fdf->cam->zoom = ft_min((WIN_WIDTH / fdf->width) / 2, (WIN_HEIGHT / fdf->height) / 2);
	ft_draw_map(fdf);

	mlx_loop(fdf->mlx_ptr);
}

