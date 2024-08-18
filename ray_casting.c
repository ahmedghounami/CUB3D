/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:11:35 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/18 19:11:48 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <i386/limits.h>
#include <stdio.h>


// void    right_rays(t_cube *cube, mlx_image_t *image, double angle)
// {
//     (void)image;
//     double y_oriz = 0;
//     double x_oriz = (int)(cube->player_X_pixel / TILE_SIZE + 1) * TILE_SIZE;
//     while (1)
//     {
//         // horizontal intersection
//         double h = cube->player_X_pixel - x_oriz;
//         y_oriz = cube->player_Y_pixel - (tan(angle) * h);
//         cube->orizontal_position_x = x_oriz;
//         cube->orizontal_position_y = y_oriz;
//         // printf("im here\n");
//         if (y_oriz >= HEIGHT || y_oriz < 0)
//             break;
//         // mlx_put_pixel(image, x_oriz, y_oriz, ft_pixel(0x00, 0xFF, 0x0F, 0xFF));
//         if (cube->map[(int)(y_oriz / TILE_SIZE)][(int)((x_oriz + 4) / TILE_SIZE)] == '1')
//             break;
//         x_oriz += TILE_SIZE;
//         if (x_oriz >= WIDTH)
//             break;
//     }
//     // red color
//     // mlx_put_pixel(image, cube->orizontal_position_x, cube->orizontal_position_y, ft_pixel(0xFF, 0x00, 0x00, 0xFF)); // red
//     double x_vert = 0;
//     double y_vert = (int)(cube->player_Y_pixel / TILE_SIZE) * TILE_SIZE;
//     while (1)
//     {
//         // vertical intersection
//         double h = cube->player_Y_pixel - y_vert;
//          x_vert = (cube->player_X_pixel - (h / tan(angle)));
//         cube->vertical_position_x = x_vert;
//         cube->vertical_position_y = y_vert;
//         if (tan(angle) == 0)
//             break;
//         if (x_vert >= WIDTH || x_vert < 0) 
//             break;
//         // mlx_put_pixel(image, x_vert, y_vert, ft_pixel(0x00, 0xFF, 0x0F, 0xFF));
//         if (cube->map[(int)(y_vert / TILE_SIZE)][(int)(x_vert / TILE_SIZE)] == '1' || cube->map[(int)((y_vert) / TILE_SIZE)][(int)(x_vert / TILE_SIZE)] == '1')
//             break;
//         y_vert -= TILE_SIZE;
//         if (y_vert <= 0)
//             break;
//     }
//     // mlx_put_pixel(image, cube->vertical_position_x, cube->vertical_position_y, ft_pixel(0xFF, 0xFF, 0x00, 0xFF)); // yellow 
// }

void    left_right_rays(t_cube *cube, mlx_image_t *image, double angle)
{
    (void)image;
    double y_oriz = 0;
    double x_oriz = (int)(cube->player_X_pixel / TILE_SIZE) * TILE_SIZE;
    if (angle > M_PI + M_PI_2 && angle <= 2 * M_PI)
        x_oriz += TILE_SIZE;
    else
        x_oriz -= 0.0001;
    while (1)
    {
        // horizontal intersection
        double h = cube->player_X_pixel - x_oriz;
         y_oriz = (cube->player_Y_pixel - (tan(angle) * h));
        cube->orizontal_position_x = x_oriz;
        cube->orizontal_position_y = y_oriz;
        if (y_oriz >= HEIGHT || y_oriz < 0)
            break;;
        if (cube->map[(int)(y_oriz / TILE_SIZE)][(int)(x_oriz / TILE_SIZE)] == '1')
            break;
        // if (cube->map[(int)(y_oriz / TILE_SIZE)][(int)(x_oriz / TILE_SIZE)] == '1')
        //     break;
        if (angle > M_PI + M_PI_2 && angle <= 2 * M_PI)
            x_oriz += TILE_SIZE;
        else
            x_oriz -= TILE_SIZE;
        if (x_oriz <= 0 || x_oriz >= WIDTH)
            break;
    }
    double x_vert = 0;
    double y_vert = (int)(cube->player_Y_pixel / TILE_SIZE) * TILE_SIZE - 0.0001;
    while(1)
    {
        double h = cube->player_Y_pixel - y_vert;
         x_vert = (cube->player_X_pixel - (h / tan(angle)));
        cube->vertical_position_x = x_vert;
        cube->vertical_position_y = y_vert;
        if (tan(angle) == 0)
            break;
        if (x_vert >= WIDTH || x_vert < 0)
            break;
        if (cube->map[(int)(y_vert / TILE_SIZE)][(int)(x_vert / TILE_SIZE)] == '1')
            break;
        y_vert -= TILE_SIZE;
        if (y_vert <= 0)
            break;
    }
}

void    down_rightrays(t_cube *cube, mlx_image_t *image, double angle)
{
    (void)image;
    double x_ver =   0;
    double y_ver = (int)(cube->player_Y_pixel / TILE_SIZE + 1) * TILE_SIZE;
    while (1)
    {
        double h = cube->player_Y_pixel - y_ver;
         x_ver = (cube->player_X_pixel - (h / tan(angle)));
        cube->orizontal_position_x = x_ver;
        cube->orizontal_position_y = y_ver;
        if (x_ver >= WIDTH || x_ver < 0)
            break;
        if (cube->map[(int)(y_ver / TILE_SIZE)][(int)(x_ver / TILE_SIZE)] == '1')
            break;
        y_ver += TILE_SIZE;
        if (y_ver >= WIDTH)
            break;
    }
    double y_oriz = 0;
    double x_oriz = (int)(cube->player_X_pixel / TILE_SIZE + 1) * TILE_SIZE;
    while (1)
    {
        double h = cube->player_X_pixel - x_oriz;
         y_oriz = (cube->player_Y_pixel - (tan(angle) * h));
        cube->vertical_position_x = x_oriz;
        cube->vertical_position_y = y_oriz;
        if (tan(angle) == 0)
            break;
        if (y_oriz >= HEIGHT || y_oriz < 0)
            return;
        
        if (cube->map[(int)(y_oriz / TILE_SIZE)][(int)(x_oriz / TILE_SIZE)] == '1')
            break;
        x_oriz += TILE_SIZE;
        if (x_oriz >= WIDTH)
            break;
    }
}

void    down_leftrays(t_cube *cube, mlx_image_t *image, double angle)
{
    (void)image;
    double x_oriz = (int)(cube->player_X_pixel / TILE_SIZE) * TILE_SIZE - 0.0001;
    double y_oriz = 0;
    while (1)
    {
        double h = cube->player_X_pixel - x_oriz;
         y_oriz = (cube->player_Y_pixel - (tan(angle) * h));
        cube->vertical_position_x = x_oriz;
        cube->vertical_position_y = y_oriz;
        if (tan(angle) == 0)
            break;
        if (y_oriz >= HEIGHT || y_oriz < 0)
            break;
        if (cube->map[(int)(y_oriz / TILE_SIZE)][(int)(x_oriz / TILE_SIZE)] == '1' )
            break;
        x_oriz -= TILE_SIZE;
        if (x_oriz < 0)
            break;
    }
    double y_vert = (int)(cube->player_Y_pixel / TILE_SIZE + 1) * TILE_SIZE;
    double x_vert = 0;
    while (1)
    {
        double h = cube->player_Y_pixel - y_vert;
         x_vert = (cube->player_X_pixel - (h / tan(angle)));
        cube->orizontal_position_x = x_vert;
        cube->orizontal_position_y = y_vert;
        if (x_vert >= WIDTH || x_vert < 0)
            break;
        if (cube->map[(int)(y_vert / TILE_SIZE)][(int)(x_vert / TILE_SIZE)] == '1' )
            break;
        y_vert += TILE_SIZE;
        if (y_vert >= HEIGHT)
           break;
    }
}
