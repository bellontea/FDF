#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf fdf;
	int fd;
	t_map *map;

	if (argc != 2)
	{
		printf("Error: too many or no arguments\n");
		return (1);
	}

	fdf.height = 0;
	fdf.width = 0;
	fdf.zoom = 30;
	fdf.map = NULL;
	fdf.width_win = 1000;
	fdf.height_win = 1000;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (1);
	}
	ft_read_map(fd, &fdf);
	close(fd);

	map = fdf.map;
	while(map)
	{
		for(int i = 0; i < fdf.width; i++)
			printf("%3d", map->coords[i]);
		map = map->next;
		printf("\n");
	}

	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.width_win, fdf.height_win, "FDF");

	ft_draw_map(&fdf);

	mlx_loop(fdf.mlx_ptr);
}

