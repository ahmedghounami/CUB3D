/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:07:33 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/28 13:40:34 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mouse_hook(t_cube *cube)
{
	static int	hidden = 0;
	static int	prev_mouse_x = -1;
	static int	prev_mouse_y = -1;

	if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT))
		(1) && (mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_HIDDEN), \
			hidden = 1);
	if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		hidden = 0;
		mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_NORMAL);
	}
	mlx_get_mouse_pos(cube->mlx, &cube->mouse_x, &cube->mouse_y);
	if (prev_mouse_x != -1 && prev_mouse_y != -1 && hidden == 1)
	{
		if (cube->mouse_x != prev_mouse_x || cube->mouse_y != prev_mouse_y)
		{
			if (cube->mouse_x > prev_mouse_x)
				cube->player_angle += ROTATION_SPEED;
			if (cube->mouse_x < prev_mouse_x)
				cube->player_angle -= ROTATION_SPEED;
		}
	}
	(1) && (prev_mouse_x = cube->mouse_x, prev_mouse_y = cube->mouse_y);
}

void	check_posssible_move(t_cube *cube, double new_x, double new_y)
{
	cube->map_x = (int)(new_x / TILE_SIZE);
	cube->map_y = (int)(new_y / TILE_SIZE);
	cube->map_x_left = (int)((new_x - 1) / TILE_SIZE);
	cube->map_x_right = (int)((new_x + 1) / TILE_SIZE);
	cube->map_y_up = (int)((new_y - 1) / TILE_SIZE);
	cube->map_y_down = (int)((new_y + 1) / TILE_SIZE);
	if (cube->map[cube->map_y][cube->map_x] == '0' ||
		cube->map[cube->map_y][cube->map_x] == 'W' ||
		cube->map[cube->map_y][cube->map_x] == 'N' ||
		cube->map[cube->map_y][cube->map_x] == 'S' ||
		cube->map[cube->map_y][cube->map_x] == 'E' ||
		cube->map[cube->map_y][cube->map_x] == '2')
	{
		if (cube->map[cube->map_y_up][cube->map_x] != '1' &&
			cube->map[cube->map_y_down][cube->map_x] != '1' &&
			cube->map[cube->map_y][cube->map_x_left] != '1' &&
			cube->map[cube->map_y][cube->map_x_right] != '1')
		{
			cube->yplayer_x_pixel = new_x;
			cube->player_y_pixel = new_y;
			cube->player_x = cube->map_x;
			cube->player_y = cube->map_y;
		}
	}
}

void	mouve_hooke(t_cube *cube)
{
	double	new_x;
	double	new_y;

	new_x = cube->yplayer_x_pixel;
	new_y = cube->player_y_pixel;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
		(1) && (new_x += cos(cube->player_angle) * SPEED, \
		new_y += sin(cube->player_angle) * SPEED);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
		(1) && (new_x -= cos(cube->player_angle) * SPEED, \
		new_y -= sin(cube->player_angle) * SPEED);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
		(1) && (new_x -= cos(M_PI_2 + cube->player_angle) * SPEED, \
		new_y -= sin(M_PI_2 + cube->player_angle) * SPEED);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
		(1) && (new_x += cos(M_PI_2 + cube->player_angle) * SPEED, \
		new_y += sin(M_PI_2 + cube->player_angle) * SPEED);
	check_posssible_move(cube, new_x, new_y);
}

void	rotation(t_cube *cube)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
		cube->player_angle -= ROTATION_SPEED;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		cube->player_angle += ROTATION_SPEED;
	cube->player_angle = normalize_angle(cube->player_angle);
}

void	ft_hook(void *param)
{
	// static int	tab_key_f = 0;
	t_cube		*cube;

	cube = (t_cube *)param;
	rotation(cube);
	mouve_hooke(cube);

	// if (mlx_is_key_down(cube->mlx, MLX_KEY_F))
	// {
	// 	if (!tab_key_f)
	// 	{
	// 		cast_ray(cube, cube->player_angle, 1);
	// 		if (cube->flag_door == 0 && cube->direction == DOOR && cube->true_distance < DOOR_DIS)
	// 			cube->map[(int)(cube->y_ray / TILE_SIZE)][(int)(cube->x_ray / TILE_SIZE)] = '2';
	// 		else
	// 			cube->flag_door = 0;
	// 	}
	// 	tab_key_f = 1;
	// }
	// else
	// 	tab_key_f = 0;
}
