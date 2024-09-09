/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:17:23 by aghounam          #+#    #+#             */
/*   Updated: 2024/09/06 12:16:24 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	draw_sprite(t_cube *cube, mlx_image_t *image, int W, int H)
{
	uint32_t start_x = 300 + W;
    uint32_t start_y = 40 + H;
    uint32_t sprite_x = 0;
    uint32_t sprite_y = 0;
    uint32_t color;

    while (sprite_y < cube->sprite->height && sprite_y + start_y < HEIGHT)
    {
        sprite_x = 0;
        while (sprite_x < cube->sprite->width && sprite_x + start_x < WIDTH)
        {
            color = get_pixel(cube->sprite, sprite_x, sprite_y);
            if (((color >> 24) & 0xFF) != 0) // Non-transparent pixel check
                mlx_put_pixel(image, start_x + sprite_x, start_y + sprite_y, color);
            sprite_x++;
        }
        sprite_y++;
    }
}

void 	sprite_animation(t_cube *cube, mlx_image_t *image)
{
	if (cube->sprite_count == 0)
		cube->sprite = mlx_load_png("sprite_anim/s1.png");
	else if (cube->sprite_count == 3)
		cube->sprite = mlx_load_png("sprite_anim/s2.png");
	else if (cube->sprite_count == 6)
		cube->sprite = mlx_load_png("sprite_anim/s3.png");
	else if (cube->sprite_count == 9)
		cube->sprite = mlx_load_png("sprite_anim/s4.png");
	else if (cube->sprite_count == 12)
		cube->sprite = mlx_load_png("sprite_anim/s5.png");
	else if (cube->sprite_count == 15)
		cube->sprite = mlx_load_png("sprite_anim/s6.png");
	cube->sprite_count++;
	if (cube->sprite_count == 18)
			cube->sprite_count = 0;
	int W = 0;
	while (W < 500) 
    {
		draw_sprite(cube, image, W, 0);
		W += 100;
	}
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	rander_weapons(mlx_image_t *image, mlx_texture_t *picture)
{
	uint32_t	start_x;
	uint32_t	start_y;
	uint32_t	weapon_x;
	uint32_t	weapon_y;
	uint32_t	color;

	weapon_x = 0;
	weapon_y = 0;
	start_x = (WIDTH - picture->width) / 2;
	start_y = HEIGHT - picture->height;
	while (weapon_y < picture->height)
	{
		weapon_x = 0;
		while (weapon_x < picture->width)
		{
			color = get_pixel(picture, weapon_x, weapon_y);
			if (((color >> 24) & 0xFF) != 0)
				mlx_put_pixel(image, start_x + weapon_x, \
				start_y + weapon_y, color);
			weapon_x++;
		}
		weapon_y++;
	}
}

void	ft_randomize(void *param)
{
	t_cube	*cube;
	static int i = 0;
	cube = (t_cube *)param;
	ft_hook(cube);
	ft_mouse_hook(cube);
	weapon_shoot(cube);
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	if (cube->init_screen == 0)
	{
		if (i == 0)
			cube->start_screen = mlx_load_png("textures/start2.png");
		else if (i == 20)
			cube->start_screen = mlx_load_png("textures/start1.png");
		i++;
		if (i == 30)
			i = 0;
		if (cube->start_screen)
			start_image(cube);
		else
			ft_error("Error\nFailed to load start screen");
	}
	else
	{
		ray_casting(cube, cube->image);
		draw_mini_map(cube, cube->image);
		rander_weapons(cube->image, cube->weapon);
		// rander_weapons(cube, cube->image, cube->sprite);
		sprite_animation(cube, cube->image);
	}	
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
}
