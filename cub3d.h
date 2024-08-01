/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/29 18:29:37 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./utils/libft.h"
# include <stdio.h> //to be removed
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

#define WIDTH  1200
#define HEIGHT 600

typedef struct s_texture
{
    int     flag;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     *f;
    int     *c;
}   t_texture;

typedef struct s_cube
{
	void	*mlx_win;
    void	*mlx;
    mlx_image_t *img;
    char    **file;
    char    **map;
    char    *fd_file;
    int     map_len;
    int     file_len;
    t_texture texture;
    int     height;
    int     width;
    double    x_pixel;
    double    y_pixel;
    double     fd;
    double     playerX;
    double     playerY;
    double     player_X_pixel;
    double     player_Y_pixel;
    double player_angle;
}   t_cube;


void    parse_textures(t_cube *cube, int i);
void    parse_mape(t_cube *cube, char *tmp1, char **tmp2, int i);
int     parse_mape2(t_cube *cube);


//utils
void    ft_init_texture(t_cube *cube);
void	is_map_valid(int argc, char *argv[], t_cube *cube);
void    get_element(t_cube *cube, char *str, char mode);
void    ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg);
void    take_map(t_cube *cube, int i, int j, int k);
void    ft_error(char *msg);
int just_space(char *str);

//tmp
void	print_file(t_cube *cube);

#endif
