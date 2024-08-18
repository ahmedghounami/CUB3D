/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/18 19:12:59 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/syslimits.h>

static mlx_image_t* image;

void get_player_position(t_cube *cube)
{
    int x = 0;
    int y = 0;
    while (cube->map[y])
    {
        x = 0;
        while (cube->map[y][x])
        {
            if (cube->map[y][x] == 'W')
            {
                cube->player_X_pixel = x * TILE_SIZE + TILE_SIZE / 2;
                cube->player_Y_pixel = y * TILE_SIZE + TILE_SIZE / 2;
                cube->playerX = x;
                cube->playerY = y;
                // return ;
            }
            x++;
        }
        y++;
    }
    cube->columx = x;
    cube->columy = y;
}
void rander_wall(int32_t color, t_cube *cube)
{
    int i;
    double distance_oriz = 0;
    double distance_vert = 0;
    double angle = cube->player_angle - M_PI / 6;
    if (angle < 0)
        angle += 2 * M_PI;
    printf("angle = %f\n", angle);
    int rays = WIDTH;
    i = 0;
    while (i < rays)
    {
        if (angle > 0 && angle <= M_PI_2)
            down_rightrays(cube, image, angle);
        else if (angle > M_PI_2 && angle <= M_PI)
            down_leftrays(cube, image, angle);
        else if ((angle >= M_PI && angle < M_PI + M_PI_2) || (angle >= M_PI + M_PI_2 && angle <= 2 * M_PI))
            left_right_rays(cube, image, angle);
        
        distance_oriz = sqrt(pow(cube->player_X_pixel - cube->orizontal_position_x, 2) + pow(cube->player_Y_pixel - cube->orizontal_position_y, 2));
        distance_vert = sqrt(pow(cube->player_X_pixel - cube->vertical_position_x, 2) + pow(cube->player_Y_pixel - cube->vertical_position_y, 2));
        double raydistance;
        double wallstripheight;
        if (distance_oriz > distance_vert)
            raydistance = distance_vert;
        else
            raydistance = distance_oriz;
        wallstripheight = (WIDTH / raydistance) * 64;
        int32_t color = ft_pixel(0xFF, 0x00, 0x00, 0xFF);
        int x = i;
        double startY = (HEIGHT / 2) - (wallstripheight / 2);
        double endY = startY + wallstripheight;
        for (int y = startY; y < endY; y++) {
            if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                mlx_put_pixel(image, x, y, color);
            }
        }
        angle += FOV / WIDTH;
        i++;
    }       
}

void ft_randomize(void* param)
{
    t_cube* cube = (t_cube *)param;
    mlx_delete_image(cube->mlx, image);
    image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
    mlx_image_to_window(cube->mlx, image, 0, 0);
    // rander_map(cube, image);
    rander_wall(ft_pixel(0xFF, 0x00, 0x00, 0xFF), cube); // Red
}

void ft_hook(void* param)
{
    t_cube *cube = (t_cube *)param;

    if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(cube->mlx);
    if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
    {
        cube->player_angle -= 0.02;
        if (cube->player_angle < 0)
            cube->player_angle += 2 * M_PI;
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
    {
        cube->player_angle += 0.02;
        cube->player_angle = fmod(cube->player_angle, 2 * M_PI);
    }
    double new_x = cube->player_X_pixel;
    double new_y = cube->player_Y_pixel;

    if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
    {
        new_x += cos(cube->player_angle) * 1; 
        new_y += sin(cube->player_angle) * 1;
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
    {
        new_x -= cos(cube->player_angle) * 1; 
        new_y -= sin(cube->player_angle) * 1; 
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
    {
        new_x -= cos(M_PI_2 + cube->player_angle) * 1;
        new_y -= sin(M_PI_2 + cube->player_angle) * 1;
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
    {
        new_x += cos(M_PI_2 + cube->player_angle) * 1;
        new_y += sin(M_PI_2 + cube->player_angle) * 1;
    }
    if (cube->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == '0' || cube->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 'W')
    {
        cube->player_X_pixel = new_x;
        cube->player_Y_pixel = new_y;
    }
    ft_randomize(cube);
}

t_cube* init_game(void) {
    t_cube *cube = malloc(sizeof(t_cube)); // Allocated on the heap
    if (!cube) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    cube->player_angle = 0.0;
    return cube; // Safe: Returning a pointer to heap memory
}

int main(int argc, char **argv)
{
    t_cube cube;

    is_map_valid(argc, argv, &cube);
    parse_textures(&cube, 0);
    parse_mape(&cube, NULL, NULL, 6);
    int a = parse_mape2(&cube);
    if (a == 1)                                              
        ft_error("Error : Map is invalid 2\n");

    cube.mlx = mlx_init((int32_t)WIDTH , (int32_t)HEIGHT, "MLX42", false);
    image = mlx_new_image(cube.mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
    get_player_position(&cube);
    
    cube.player_angle = 0;
    mlx_image_to_window(cube.mlx, image, 0, 0);
    ft_randomize(&cube);
    mlx_loop_hook(cube.mlx, ft_hook, &cube);
    mlx_loop(cube.mlx);
    return (EXIT_SUCCESS);
}
