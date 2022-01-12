

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

typedef struct	s_map
{
	int				*coords;
	int				y;
	struct s_map	*next;
}				t_map;

typedef struct	s_fdf
{
	int			width;
	int			height;
	t_map		*map;
	void		*mlx_ptr;
	void		*win_ptr;
	int			width_win;
	int			height_win;
	int			zoom;
}				t_fdf;


t_map	*ft_init_map(int y, char **coords, int width);
void	ft_read_map(int fd, t_fdf *fdf);
void 	ft_draw_map(t_fdf *fdf);