/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:11:35 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/30 12:55:10 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_wall(double x, double y, t_cube *cube)
{

    int map_x = floor(x / TILE_SIZE);
    int map_y = floor(y / TILE_SIZE);
    if (map_x < 0 || map_x >= cube->columx || map_y < 0 || map_y >= cube->columy)
        return (1);
    if ((int)ft_strlen(cube->map[map_y]) <= map_x)
        return (1);
    if (cube->map[map_y][map_x] == '1')
        return (1);
    return (0);
}

void get_oriz(t_cube *cube, double angle)
{
    double y_intercept = floor(cube->player_y_pixel / TILE_SIZE) * TILE_SIZE;
    if (cube->facing_down)
        y_intercept += TILE_SIZE;
    double x_intercept = cube->yplayer_x_pixel + (y_intercept - cube->player_y_pixel) / tan(angle);
    double y_step = TILE_SIZE;
    double x_step = TILE_SIZE / tan(angle);
    if (cube->facing_up)
        y_step *= -1;
    
    if (cube->facing_right && x_step < 0)
        x_step *= -1;
    if (cube->facing_left && x_step > 0)
        x_step *= -1;
    
    if (cube->facing_up)
        y_intercept -= 0.0001;
    while (1)
    {
        if (check_wall(x_intercept, y_intercept, cube))
        {
            cube->orizontal_position_x = x_intercept;
            cube->orizontal_position_y = y_intercept;
            break;
        }
        else
        {
            x_intercept += x_step;
            y_intercept += y_step;
        }
    }
}    

void get_vert(t_cube *cube, double angle)
{
    double x_intercept = floor(cube->yplayer_x_pixel / TILE_SIZE) * TILE_SIZE;
    if (cube->facing_right)
        x_intercept += TILE_SIZE;
    double y_intercept = cube->player_y_pixel + (x_intercept - cube->yplayer_x_pixel) * tan(angle);

    double x_step = TILE_SIZE;
    double y_step = TILE_SIZE * tan(angle);
    if (cube->facing_left)
        x_step *= -1;
    
    if (cube->facing_down && y_step < 0)
        y_step *= -1;
    if (cube->facing_up && y_step > 0)
        y_step *= -1;

    if (cube->facing_left)
        x_intercept -= 0.0001; 
    while (1)
    {
        if (check_wall(x_intercept, y_intercept, cube))
        {
            cube->vertical_position_x = x_intercept;
            cube->vertical_position_y = y_intercept;
            break;
        }
        else
        {
            x_intercept += x_step;
            y_intercept += y_step;
        }
    }
}

double smallest_distance(t_cube *cube, double angle)
{
    (void)angle;
    double distance_oriz = sqrt(pow(cube->yplayer_x_pixel - cube->orizontal_position_x, 2) + pow(cube->player_y_pixel - cube->orizontal_position_y, 2));
    double distance_vert = sqrt(pow(cube->yplayer_x_pixel - cube->vertical_position_x, 2) + pow(cube->player_y_pixel - cube->vertical_position_y, 2));
    if (distance_oriz < distance_vert)
    {
        cube->ray_intercept = cube->orizontal_position_x;
        if (cube->facing_up)
            cube->direction = WEST;
        else if (cube->facing_down)
            cube->direction = EAST;
        return (distance_oriz);
    }
    cube->ray_intercept = cube->vertical_position_y;
    if (cube->facing_left)
        cube->direction = NORTH;
    else if (cube->facing_right)
        cube->direction = SOUTH;
    return (distance_vert);
}
void cast_ray(t_cube *cube, double angle)
{
    angle = normalize_angle(angle);
    cube->facing_down = angle > 0 && angle < M_PI;
    cube->facing_up = !cube->facing_down;
    cube->facing_right = angle < (0.5 * M_PI) || angle > (1.5 * M_PI);
    cube->facing_left = !cube->facing_right;
    get_oriz(cube, angle);
    get_vert(cube, angle);
    cube->true_distance = smallest_distance(cube, angle);
}

void ray_casting(t_cube *cube, mlx_image_t *image)
{
    double angle = normalize_angle(cube->player_angle) - (FOV / 2);
    int rays = -1;
    // rander_map(cube, image);
    while (++rays < WIDTH)
    {
        cast_ray(cube, angle);
        // draw_utils(cube, image, angle);
        render_wall(cube, image, angle, rays);
        angle += FOV / WIDTH;
        angle = normalize_angle(angle);
    }
}
