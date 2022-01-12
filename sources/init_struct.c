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