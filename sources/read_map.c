#include "fdf.h"

int	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
    return (i);
}

int ft_size_arr(char **arr)
{
    int i;

    i = 0;
    while(arr[i])
        i++;
    return (i);
}

void find_z_min_max(t_fdf *fdf)
{
    t_map *map = fdf->map;
    int i;

    i = 0;
    while (i < fdf->height)
    {
        if (fdf->z_max < map->z_max)
            fdf->z_max = map->z_max;
        if (fdf->z_min > map->z_min)
            fdf->z_min = map->z_min;
        map = map->next;
        i++;
    }
}

void ft_read_map(int fd, t_fdf *fdf)
{
    char    *line;
    t_map   *map;
    t_map   *prev;
    char    **coords;
    int     i;

    map = NULL;
    line = get_next_line(fd);
    i = 0;
    while (line)
    {
        coords = ft_split(line, ' ');
        if (i == 0)
            fdf->width = ft_size_arr(coords);
        map = ft_init_map(i, coords, fdf->width);
        if (i == 0)
            fdf->map = map; 
        else
            prev->next = map;
        free(line);
        ft_free_array(coords);
        line = get_next_line(fd);
        prev = map;
        map = map->next;
        i++;
    }
    fdf->height = i;
    find_z_min_max(fdf);
//    fdf->width = map->width;
}