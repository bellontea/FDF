/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:36:20 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 19:01:55 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_abs(int a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

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
