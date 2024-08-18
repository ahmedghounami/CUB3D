/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:17:20 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/18 19:06:20 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_render_pixel(int32_t x, int32_t y, int32_t color, mlx_image_t *image)
{
    int i, j;
    i = 0;
    j = 0;
    while (i < TILE_SIZE - 2)
    {
        j = 0;
        while (j < TILE_SIZE - 2)
        {
            mlx_put_pixel(image, x * TILE_SIZE + i + 1, y * TILE_SIZE + j + 1, color);
            j++;
        }
        i++;
    }
}

void    draw_utils(t_cube *cube, mlx_image_t *image, double angle)
{
    double distance_oriz = sqrt(pow(cube->orizontal_position_x - cube->player_X_pixel, 2) + pow(cube->orizontal_position_y - cube->player_Y_pixel, 2));
    double distance_vert = sqrt(pow(cube->vertical_position_x - cube->player_X_pixel, 2) + pow(cube->vertical_position_y - cube->player_Y_pixel, 2));
    if (distance_vert < distance_oriz)
    {
        int j = 0;
        while (j < distance_vert)
        {
            int x = cube->player_X_pixel + j * cos(angle);
            int y = cube->player_Y_pixel + j * sin(angle);
            mlx_put_pixel(image, x, y, ft_pixel(0xFF, 0x00, 0x00, 0xFF));
            // if (cube->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
            //     break;
            j++;
        }
    }
    else
        {
            int j = 0;
            while (j < distance_oriz)
            {
                int x = cube->player_X_pixel + j * cos(angle);
                int y = cube->player_Y_pixel + j * sin(angle);
                mlx_put_pixel(image, x, y, ft_pixel(0xFF, 0x00, 0x00, 0xFF));
                // if (cube->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
                //     break;
                j++;
            }
        }
}

void draw_rays(t_cube *cube, mlx_image_t *image)
{
    int i;
    double angle = cube->player_angle - M_PI / 6;
    if (angle < 0)
        angle += 2 * M_PI;
    else if (angle > 2 * M_PI)
    angle -= 2 * M_PI;
    
    int rays = WIDTH;
    i = 0;
    while (i < rays)
    {
        cube->RIGHT_UP_RAYS = (angle >= M_PI + M_PI_2 && angle <= 2 * M_PI);
        cube->RIGHT_DOWN_RAYS = (angle >= 0 && angle <= M_PI_2);
        cube->LEFT_UP_RAYS = (angle > M_PI && angle <= M_PI + M_PI_2);
        cube->LEFT_DOWN_RAYS = (angle > M_PI_2 && angle <= M_PI);
        if (cube->RIGHT_DOWN_RAYS)
            down_rightrays(cube, image, angle);
        else if (cube->LEFT_DOWN_RAYS)
            down_leftrays(cube, image, angle);
        else if (cube->LEFT_UP_RAYS || cube->RIGHT_UP_RAYS)
            left_right_rays(cube, image, angle);
        draw_utils(cube, image, angle);
        angle += FOV / rays;
        angle = fmod(angle, 2 * M_PI);
        i++;
    }
}

void rander_map(t_cube *cube, mlx_image_t *image)
{

    int x = 0;
    int y = 0;
     while (cube->map[x])
    {
        y = 0;
        while (cube->map[x][y])
        {
            if (cube->map[x][y] == '1')
               ft_render_pixel( y, x, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF), image); // White
            else if (cube->map[x][y] == '0' || cube->map[x][y] == ' ')
               ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF), image); // Black
            else if (cube->map[x][y] == 'W')
                ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF), image); // Black
            y++;
        }
        x++;
    }
    int i, j;
    for (i = 0; i < TILE_SIZE / 16; i++)
    {
        for (j = 0; j < TILE_SIZE / 16; j++)
        {
            mlx_put_pixel(image, cube->player_X_pixel + i, cube->player_Y_pixel + j, ft_pixel(0x00, 0xFF, 0x00, 0xFF)); // Green
            mlx_put_pixel(image, cube->player_X_pixel - i, cube->player_Y_pixel + j, ft_pixel(0x00, 0xFF, 0x00, 0xFF)); // Green
            mlx_put_pixel(image, cube->player_X_pixel + i, cube->player_Y_pixel - j, ft_pixel(0x00, 0xFF, 0x00, 0xFF)); // Green
            mlx_put_pixel(image, cube->player_X_pixel - i, cube->player_Y_pixel - j, ft_pixel(0x00, 0xFF, 0x00, 0xFF)); // Green
        }
    }
    draw_rays(cube, image);
}

