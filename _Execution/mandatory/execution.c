/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:37:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/06 10:13:11 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	execution(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	key_hooks(cube, &cube->player, 0.0, 0.0);
	key_rotations(cube->mlx, &cube->player);
	ray_casting(cube, &cube->player);
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
		ft_error("Error : Image not found\n");
}

void	init_exec(t_cube *cube, t_player *player)
{
	cube->mlx = mlx_init((int32_t)WIDTH, (int32_t)HEIGHT, "MLX42", false);
	if (!cube->mlx)
		ft_error("Error : MLX not found\n");
	player->x = (player->x * TILE) + ((double)TILE / 2);
	player->y = (player->y * TILE) + ((double)TILE / 2);
	(player->way == 'E') && (player->rotation_angle = 0);
	(player->way == 'S') && (player->rotation_angle = M_PI / 2);
	(player->way == 'W') && (player->rotation_angle = M_PI);
	(player->way == 'N') && (player->rotation_angle = 3 * M_PI / 2);
	cube->window.t1 = mlx_load_png(cube->window.no);
	cube->window.t2 = mlx_load_png(cube->window.so);
	cube->window.t3 = mlx_load_png(cube->window.ea);
	cube->window.t4 = mlx_load_png(cube->window.we);
	cube->window.sky = mlx_load_png("textures/sky.png");
	if (!cube->window.t1 || !cube->window.t2
		|| !cube->window.t3 || !cube->window.t4 || !cube->window.sky)
		ft_error("Error : Texture not found\n");
	mlx_loop_hook(cube->mlx, execution, cube);
	mlx_loop(cube->mlx);
}
