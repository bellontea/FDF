

#include <mlx.h>
#include "libft.h"
#include "get_next_line.h"
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
# define COLOR_1 0x33ccff
# define COLOR_2 0x65c0f2
# define COLOR_3 0x9fb1e4
# define COLOR_4 0xc7a7da
# define COLOR_5 0xff99cc

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_map
{
	int				*coords;
	int				y;
	struct s_map	*next;
	int				z_max;
	int 			z_min;
}				t_map;

typedef struct	s_dot
{
	int		x;
	int		y;
	int		z;
	int			color;
}				t_dot;


typedef struct	s_cam
{
	float		alpha;
	float		beta;
	float		gamma;
	int			zoom;
	int			shift_x;
	int			shift_y;	
	int			prev_shift_x;
	int			prev_shift_y;
	int			zoom_count;
	int			projection;
}				t_cam;


typedef struct	s_fdf
{
	int			width;
	int			height;
	t_map		*map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_cam		*cam;
	t_img	img;
	int			z_min;
	int			z_max;
}				t_fdf;

t_map	*ft_init_map(int y, char **coords, int width);
void	ft_read_map(int fd, t_fdf *fdf);
void 	ft_draw_map(t_fdf *fdf);
void set_win_close(t_fdf *fdf);
t_fdf *ft_init_fdf();
t_dot	ft_init_dot(int x, int y, int z, t_fdf *fdf);
t_dot	ft_update(t_fdf *fdf, t_dot dot);
int get_color(t_dot current, t_dot start, t_dot end, int delta_x, int delta_y);
int	get_default_color(int z, t_fdf *fdf);