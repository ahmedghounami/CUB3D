/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/07 16:00:48 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "../Utils/libft.h"
# include "../../MLX42/include/MLX42/MLX42.h"

# define PI 3.14159265
# define WIDTH 1000
# define HEIGHT 600
# define TILE 22
# define PROJECT_PLANE 866.0254037844
# define ROTATION_SPEED 0.06030300258
# define MOVE_SPEED 1.2
# define FOV 1.0471975511965976
# define FOV_ANGLE 1.0471975512

typedef struct s_player
{
	double	x;
	double	y;
	char	way;
	double	rotation_angle;
	int		facing_up;
	int		facing_down;
	int		facing_left;
	int		facing_right;
	double	true_distance;
	double	vertical_x;
	double	vertical_y;
	double	orizontal_y;
	double	orizontal_x;
}	t_player;

typedef struct s_window
{
	int				*c;
	int				*f;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				flag;
	int				width;
	int				height;
	mlx_texture_t	*t1;
	mlx_texture_t	*t2;
	mlx_texture_t	*t3;
	mlx_texture_t	*t4;
	mlx_texture_t	*sky;
	double			ray_intercept;
}	t_win;

typedef struct s_pars
{
	int			fd;
	char		**map;
	char		**file;
	int			map_len;
	char		*fd_file;
	int			len_file;
}	t_pars;

typedef struct s_execution
{
	int		i;
	int		ray;
	int		color;
	double	ray_angle;
	int		texture_x;
	int		texture_y;
	int		walltop_pixel;
	int		wallbottom_pixel;
	double	wallstripheight;
	double	correct_distance;
}	t_exec;

typedef struct s_cube
{
	void		*mlx;
	mlx_image_t	*image;
	t_player	player;
	t_win		window;
	t_pars		pars;
	t_exec		exec;
}	t_cube;

void	is_map_valid(int argc, char *argv[], t_cube *cube);
void	check_map_name(int argc, char *name, int i);
void	initialize_list(t_cube *cube, char *map);
int		check_elem(char **map, t_cube *cube);
void	get_element(t_cube *cube, char *str, char mode);
int		check_map(char **map, int x, int y);
int		skip_space(char *str, int mode);
int		skip_line(t_pars *pars, int i, int mode);
void	init_exec(t_cube *cube, t_player *player);
void	execution(void *arg);
void	key_hooks(t_cube *cube, t_player *player, double move_x, double move_y);
void	key_rotations(void *mlx, t_player *player);
void	ray_casting(t_cube *cube, t_player *player);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int		get_pixel(mlx_texture_t *texture, int x, int y);
void	ft_pixel_to_image(mlx_image_t *image, int x, int y, uint32_t color);
double	normalize_angle(double angle);
void	render_window(t_cube *cube, t_exec *exec, t_player *player, t_win *win);
void	ft_eraser(t_cube *cube, void *tmp, int *rgb, char *msg);
int		ft_error(char *msg);

#endif
