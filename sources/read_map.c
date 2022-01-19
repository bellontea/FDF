/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:01:45 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:48:22 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_size_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_find_z_min_max(t_fdf *fdf)
{
	t_map	*map;
	int		i;

	i = 0;
	map = fdf->map;
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

void	ft_read_map(int fd, t_fdf *fdf)
{
	char	*line;
	t_map	*map;
	t_map	*prev;
	char	**coords;
	int		i;

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
		line = get_next_line(fd);
		prev = map;
		map = map->next;
		i++;
	}
	fdf->height = i;
}
