

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

# define WIN_WIDTH 1800
# define WIN_HEIGHT	1000

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
}				t_fdf;

t_map	*ft_init_map(int y, char **coords, int width);
void	ft_read_map(int fd, t_fdf *fdf);
void 	ft_draw_map(t_fdf *fdf);
void set_win_close(t_fdf *fdf);
t_fdf *ft_init_fdf();
t_dot	ft_init_dot(int x, int y, int z);
t_dot	ft_update(t_fdf *fdf, t_dot dot);