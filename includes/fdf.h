/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:49:10 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:48:22 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <math.h>
# include "keys.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT	1080
# define PARALLEL 0
# define ISOMETRIC 1
# define COLOR_1 0x0066ff
# define COLOR_2 0x4c57f0
# define COLOR_3 0x834ce5
# define COLOR_4 0xbd40d9
# define COLOR_5 0xff33cc
# define BACKGROUND 0x222222

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_map
{
	int				*coords;
	int				y;
	struct s_map	*next;
	int				z_max;
	int				z_min;
}				t_map;

typedef struct s_dot
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_dot;

typedef struct s_steps
{
	double	x;
	double	y;
}				t_steps;

typedef struct s_cam
{
	float		alpha;
	float		beta;
	float		gamma;
	int			zoom;
	int			shift_x;
	int			shift_y;	
	int			prev_shift_x;
	int			prev_shift_y;
	int			projection;
}				t_cam;

typedef struct s_fdf
{
	int			width;
	int			height;
	t_map		*map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_cam		*cam;
	t_img		img;
	int			z_min;
	int			z_max;
}				t_fdf;

t_map	*ft_init_map(int y, char **coords, int width);
void	ft_read_map(int fd, t_fdf *fdf);
void	ft_draw_map(t_fdf *fdf);
t_fdf	*ft_init_fdf(void);
t_dot	ft_init_dot(int x, int y, int z, t_fdf *fdf);
t_dot	ft_update(t_fdf *fdf, t_dot dot);
int		get_color(t_dot current, t_dot start, t_dot end, t_dot delta);
int		get_default_color(int z, t_fdf *fdf);
int		ft_win_close(t_fdf *fdf);
int		ft_key_hooks(int keycode, t_fdf *fdf);
void	ft_find_z_min_max(t_fdf *fdf);
int		ft_free_array(char **array);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	ft_fill_line(t_map *map, char **coords_char, int **coords);
t_fdf	*ft_fdf_malloc(void);
void	ft_change_proection(int keycode, t_fdf *fdf);
void	ft_mouse_zoom(int keycode, t_fdf *fdf);
void	ft_shift(int keycode, t_fdf *fdf);
int		rotate(int keycode, t_fdf *fdf);

#endif