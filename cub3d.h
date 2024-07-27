/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/26 18:18:42 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./lib/libft.h"
# include <stdio.h> //to be removed
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>

typedef struct s_texture
{
    int     flag;
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     *floor;
    int     *ceiling;
}   t_texture;

typedef struct s_cube
{
	void	*mlx_win;
    void	*mlx;
    char    **file;
    char   *fd_file;
    char    **map;
    int     map_len;
    int     file_len;
    t_texture texture;
    int     fd;
}   t_cube;



void    parse_textures(t_cube *cube, int i);
void    parse_mape(t_cube *cube);


//utils
void	is_map_valid(int argc, char *argv[], t_cube *cube);
void    get_element(t_cube *cube, char *str, char mode);
void    ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg);
int     is_an_element(char *str);
void    ft_error(char *msg);

//tmp
void	print_file(t_cube *cube);
int count_elem(char **map);
int check_map(char **map);
int parse_mape_2(t_cube *cube);

#endif
 