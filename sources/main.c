/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:00:09 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:48:22 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	int		fd;
	t_map	*map;

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
	if (fdf == NULL)
		ft_win_close(fdf);
	ft_read_map(fd, fdf);
	ft_find_z_min_max(fdf);
	close(fd);
	fdf->cam->zoom = ft_min((WIN_WIDTH / fdf->width) / 2,
			(WIN_HEIGHT / fdf->height) / 2);
	ft_draw_map(fdf);
	mlx_loop(fdf->mlx_ptr);
}
