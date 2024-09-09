/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:19:44 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/27 12:46:43 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_player_position(t_cube *cube)
{
    int x = 0;
    int y = 0;
    cube->columx = 0;
    cube->columy = 0;
    while (cube->map[y])
    {
        x = 0;
        while (cube->map[y][x])
        {
            if (cube->map[y][x] == 'W' || cube->map[y][x] == 'N' || cube->map[y][x] == 'S' || cube->map[y][x] == 'E')
            {
                cube->yplayer_x_pixel = x * TILE_SIZE + TILE_SIZE / 2;
                cube->player_y_pixel = y * TILE_SIZE + TILE_SIZE / 2;
                cube->player_x = x;
                cube->player_y = y;
            }
            x++;
            if (cube->columx < x)
                cube->columx = x;
            
        }
        y++;
        if (cube->columy < y)
            cube->columy = y;
    }
}
