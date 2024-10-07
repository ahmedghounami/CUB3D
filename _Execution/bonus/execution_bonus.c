/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:37:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/07 15:22:38 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	sprite_load(t_cube *cube)
{
	cube->sprite.sprite[0] = mlx_load_png("textures/s1.png");
	cube->sprite.sprite[1] = mlx_load_png("textures/s2.png");
	cube->sprite.sprite[2] = mlx_load_png("textures/s3.png");
	cube->sprite.sprite[3] = mlx_load_png("textures/s4.png");
	cube->sprite.sprite[4] = mlx_load_png("textures/s5.png");
	cube->sprite.sprite[5] = mlx_load_png("textures/s6.png");
	if (!cube->sprite.sprite[0] || !cube->sprite.sprite[1]
		|| !cube->sprite.sprite[2] || !cube->sprite.sprite[3]
		|| !cube->sprite.sprite[4] || !cube->sprite.sprite[5])
		ft_error("Error : Sprite not found\n");
}

void	sprite_animation(t_cube *cube, t_sprite *sprite)
{
	int	w;

	if (sprite->sprite_count == 0)
		sprite->i = 0;
	else if (sprite->sprite_count == 3)
		sprite->i = 1;
	else if (sprite->sprite_count == 6)
		sprite->i = 2;
	else if (sprite->sprite_count == 9)
		sprite->i = 3;
	else if (sprite->sprite_count == 12)
		sprite->i = 4;
	else if (sprite->sprite_count == 15)
		sprite->i = 5;
	sprite->sprite_count++;
	if (sprite->sprite_count == 18)
		sprite->sprite_count = 0;
	w = 0;
	while (w < 500)
	{
		draw_sprite(cube, sprite, w, 0);
		w += 100;
	}
}

void	weapon_shoot(t_cube *cube, t_win *win)
{
	static int	shooting = 0;

	if (mlx_is_key_down(cube->mlx, MLX_KEY_SPACE))
	{
		if (shooting == 0)
			(1) && (win->weapon = mlx_load_png("textures/2.png"),
				shooting = 1);
		else if (shooting == 1)
			(1) && (win->weapon = mlx_load_png("textures/3.png"),
				shooting = 2);
		else if (shooting == 2)
			(1) && (win->weapon = mlx_load_png("textures/1.png"),
				shooting = 0);
	}
	else
		(1) && (win->weapon = mlx_load_png("textures/1.png"),
			shooting = 0);
	if (!win->weapon)
		ft_error("Error : Weapon not found\n");
}

void	execution(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	key_hooks(cube, &cube->player, 0.0, 0.0);
	mouse_hook(cube, &cube->window);
	weapon_shoot(cube, &cube->window);
	key_rotations(cube->mlx, &cube->player);
	ray_casting(cube, &cube->player);
	render_weapons(cube->image, cube->window.weapon);
	sprite_animation(cube, &cube->sprite);
	minimap(cube, &cube->player, 0, 0);
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
	cube->window.door = mlx_load_png("textures/door.png");
	cube->window.sky = mlx_load_png("textures/sky.png");
	cube->window.weapon = mlx_load_png("textures/1.png");
	if (!cube->window.t1 || !cube->window.t2 || !cube->window.t3
		|| !cube->window.t4 || !cube->window.door || !cube->window.sky
		|| !cube->window.weapon)
		ft_error("Error : Texture not found\n");
	sprite_load(cube);
	mlx_loop_hook(cube->mlx, execution, cube);
	mlx_loop(cube->mlx);
}
