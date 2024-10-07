/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:35 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/01 13:07:10 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_move(t_cube *cube, double move_x, double move_y)
{
	int	index_x;
	int	index_y;
	int	to_x;
	int	to_y;

	to_x = floor(cube->player.x + move_x) / TILE;
	to_y = floor(cube->player.y + move_y) / TILE;
	index_x = floor(cube->player.x) / TILE;
	index_y = floor(cube->player.y) / TILE;
	if (to_x < 0 || to_x >= cube->window.width || to_y < 0
		|| to_y >= cube->window.height)
		return ;
	if (cube->pars.map[to_y][to_x] == '1')
		return ;
	else if (to_x != index_x && to_y != index_y)
	{
		if (cube->pars.map[to_y][index_x] == '1'
			|| cube->pars.map[index_y][to_x] == '1')
			return ;
	}
	cube->player.x += move_x;
	cube->player.y += move_y;
}

void	key_rotations(void *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->rotation_angle += ROTATION_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->rotation_angle -= ROTATION_SPEED;
	player->rotation_angle = remainder(player->rotation_angle, 2 * M_PI);
	if (player->rotation_angle < 0)
		player->rotation_angle = (2 * M_PI) + player->rotation_angle;
	player->rotation_angle = normalize_angle(player->rotation_angle);
}

void	key_hooks(t_cube *cube, t_player *player, double move_x, double move_y)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
	{
		move_x += cos(player->rotation_angle) * MOVE_SPEED;
		move_y += sin(player->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
	{
		move_x += cos(player->rotation_angle) * -MOVE_SPEED;
		move_y += sin(player->rotation_angle) * -MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
	{
		move_x += -sin(player->rotation_angle) * MOVE_SPEED;
		move_y += cos(player->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
	{
		move_x += sin(player->rotation_angle) * MOVE_SPEED;
		move_y += -cos(player->rotation_angle) * MOVE_SPEED;
	}
	check_move(cube, move_x, move_y);
}
