/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/08 18:41:00 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../utils/libft.h"
# include <stdio.h> //to be removed
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

# define WIDTH  1792
# define HEIGHT 768
# define TILE_SIZE 64
# define MINI_MAP_T 14
# define FOV 1.0471975511965976 // 60 degrees
# define SPEED 5
# define ROTATION_SPEED 0.06
# define SPEED_MINI 1
# define DOOR_DIS 150
# define WIDRH_MINI 240
# define HEIGHT_MINI 176

enum e_deir
{
	N = 0,
	S = 1,
	W = 2,
	E = 3
};

enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
	DOOR = 4
};
typedef struct s_texture
{
	int					flag;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	int					*f;
	int					*c;
}	t_texture;

typedef struct s_cube
{
	int					sprite_count;
	int					facing_up;
	int					facing_down;
	int					facing_right;
	int					facing_left;
	double				true_distance;
	void				*mlx_win;
	void				*mlx;
	mlx_image_t			*image;
	mlx_texture_t		*wall_1;
	mlx_texture_t		*wall_2;
	mlx_texture_t		*wall_3;
	mlx_texture_t		*wall_4;
	char				**file;
	char				**map;
	char				*fd_file;
	int					map_len;
	int					file_len;
	t_texture			textures;
	int					height;
	int					width;
	int					columx;
	int					columy;
	double				fd;
	int					player_x;
	int					player_y;
	double				speed_x;
	double				speed_y;
	double				yplayer_x_pixel;
	double				player_y_pixel;
	double				player_angle;
	double				orizontal_position_x;
	double				orizontal_position_y;
	double				vertical_position_x;
	double				vertical_position_y;
	int32_t				mouse_x;
	int32_t				mouse_y;
	double				ray_intercept;
	enum e_direction	direction;
	enum e_deir			player_init_dir;
	// int					x_ray;
	// int					y_ray;
	int					map_x;
	int					map_y;
	int					map_x_left;
	int					map_x_right;
	int					map_y_up;
	int					map_y_down;
}	t_cube;

// Parsing
void	parse_textures(t_cube *cube, int i);
void	parse_mape(t_cube *cube, char *tmp1, char **tmp2, int i);
int		parse_mape2(t_cube *cube);

//utils parsing
void	ft_init_texture(t_cube *cube);
void	is_map_valid(int argc, char *argv[], t_cube *cube);
void	get_element(t_cube *cube, char *str);
void	ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg);
void	take_map(t_cube *cube, int i, int j, int k);
void	ft_error(char *msg);
int		just_space(char *str);
void	print_file(t_cube *cube);

// execution
void	ft_randomize(void *param);
void	ft_hook(void *param);

// mini_map

void	draw_mini_map(t_cube *cube, mlx_image_t *image);

// utils execution
double	normalize_angle(double angle);
void	ft_render_pixel(int32_t x, int32_t y, int32_t color,
			mlx_image_t *image);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	rander_map(t_cube *cube, mlx_image_t *image);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	get_player_position(t_cube *cube);
void	ft_hook(void *param);
void	ft_mouse_hook(t_cube *cube);
void weapon_shoot(t_cube *cube);

// ray_casting
void	ray_casting(t_cube *cube, mlx_image_t *image);
void	draw_utils(t_cube *cube, mlx_image_t *image, double angle);
void	render_wall(t_cube *cube, mlx_image_t *image, double angle, double ray);
int		get_pixel(mlx_texture_t *texture, int x, int y);
void	cast_ray(t_cube *cube, double angle);

#endif
