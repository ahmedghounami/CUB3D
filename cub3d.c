/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/29 19:34:09 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/syslimits.h>

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void get_player_position(t_cube *cube)
{
    int x = 0;
    int y = 0;
    while (cube->map[x])
    {
        y = 0;
        while (cube->map[x][y])
        {
            if (cube->map[x][y] == 'W')
            {
                cube->player_X_pixel = y * cube->x_pixel + cube->x_pixel / 2;
                cube->player_Y_pixel = x * cube->y_pixel + cube->y_pixel / 2;
                cube->playerX = y;
                cube->playerY = x;
                return ;
            }
            y++;
        }
        x++;
    }
}
void ft_render_pixel_player(int32_t color, t_cube *cube)
{
    int i, j;
    int title;
    if (cube->x_pixel < cube->y_pixel)
        title = cube->x_pixel;
    else
        title = cube->y_pixel;
    // Draw a circle for the player
    for (i = 0; i < title / 4; i++)
    {
        for (j = 0; j < title / 4; j++)
        {
            mlx_put_pixel(image, cube->player_X_pixel + i, cube->player_Y_pixel + j, color);
            mlx_put_pixel(image, cube->player_X_pixel - i, cube->player_Y_pixel + j, color);
            mlx_put_pixel(image, cube->player_X_pixel + i, cube->player_Y_pixel - j, color);
            mlx_put_pixel(image, cube->player_X_pixel - i, cube->player_Y_pixel - j, color);
        }
    }

    // Draw direction line
    i = 0;
    double angle = cube->player_angle;
    int k = 0;
    while (k < 160)
    {
        while (1)
        {
            int x = (int)(cube->player_X_pixel + cos(angle) * i);
            int y = (int)(cube->player_Y_pixel + sin(angle) * i);
            if (cube->map[(int)(y / cube->y_pixel)][(int)(x / cube->x_pixel)] == '1')
                break;
            mlx_put_pixel(image, x, y, color);
            i++;
        }
        angle += 0.003;
        k++;
        i = 0;
    }
    angle = cube->player_angle;
    k = 0;
    while (k < 160)
    {
        while (1)
        {
            int x = (int)(cube->player_X_pixel + cos(angle) * i);
            int y = (int)(cube->player_Y_pixel + sin(angle) * i);
            if (cube->map[(int)(y / cube->y_pixel)][(int)(x / cube->x_pixel)] == '1')
                break;
            mlx_put_pixel(image, x, y, color);
            i++;
        }
        angle -= 0.003;
        k++;
        i = 0;
    }
    
}


void ft_render_pixel(int32_t x, int32_t y, int32_t color, t_cube *cube)
{
    int i, j;
    i = 0;
    j = 0;
    while (i < cube->x_pixel - 2)
    {
        j = 0;
        while (j < cube->y_pixel - 2)
        {
            mlx_put_pixel(image, x * cube->x_pixel + i, y * cube->y_pixel + j, color);
            j++;
        }
        i++;
    }
}

void ft_randomize(void* param)
{
    t_cube* cube = (t_cube *)param;
    int x = 0;
    int y = 0;
    mlx_delete_image(cube->mlx, image);
    image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
    mlx_image_to_window(cube->mlx, image, 0, 0);

    while (cube->map[x])
    {
        y = 0;
        while (cube->map[x][y])
        {
            if (cube->map[x][y] == '1')
               ft_render_pixel( y, x, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF), cube); // White
            else if (cube->map[x][y] == '0' || cube->map[x][y] == ' ')
               ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF), cube); // Black
            else if (cube->map[x][y] == 'W')
                ft_render_pixel( y, x, ft_pixel(0x00, 0x00, 0x00, 0xFF), cube); // Turquoise

            y++;
        }
        x++;
    }
    ft_render_pixel_player(ft_pixel(0xFF, 0x00, 0x00, 0xFF), cube); // Red
}

void ft_hook(void* param)
{
    t_cube *cube = (t_cube *)param;

    if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(cube->mlx);

    // Rotate player
    if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
    {
        cube->player_angle -= 0.04;
        printf("angle = %f\n", cube->player_angle);
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
        cube->player_angle += 0.04;

    double new_x = cube->player_X_pixel;
    double new_y = cube->player_Y_pixel;

    if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
    {
        new_x += cos(cube->player_angle) * 1; // Adjust speed as needed
        new_y += sin(cube->player_angle) * 1;
        printf("x %f\n", new_x);
        printf("y %f\n", new_y);
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
    {
        new_x -= cos(cube->player_angle) * 1; // Adjust speed as needed
        new_y -= sin(cube->player_angle) * 1; // Adjust speed as needed
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
    {
        new_x -= cos(M_PI_2 + cube->player_angle) * 1; // Adjust speed as needed
        new_y -= sin(M_PI_2 + cube->player_angle) * 1; // Adjust speed as needed
        printf("Ax %f\n", new_x);
    }
    if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
    {
        new_x += cos(M_PI_2 + cube->player_angle) * 1; // Adjust speed as needed
        new_y += sin(M_PI_2 + cube->player_angle) * 1; // Adjust speed as needed
        printf("Dx %f\n", new_x);
    }
    if (cube->map[(int)(new_y / cube->y_pixel)][(int)(new_x / cube->x_pixel)] != '1')
    {
        cube->player_X_pixel = new_x;
        cube->player_Y_pixel = new_y;
    }

    ft_randomize(cube);
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
	
    cube.x_pixel = (float)WIDTH / (float)cube.width;
    cube.y_pixel = (float)HEIGHT / (float)cube.height;
    printf("x_pixel = %f\n", cube.x_pixel);
    printf("y_pixel = %f\n", cube.y_pixel);
    get_player_position(&cube);
    
    cube.player_angle = 0;
    // Calculate player's pixel position
    mlx_image_to_window(cube.mlx, image, 0, 0);
    ft_randomize(&cube);
    mlx_loop_hook(cube.mlx, ft_hook, &cube);
    mlx_loop(cube.mlx);
    return (EXIT_SUCCESS);
}