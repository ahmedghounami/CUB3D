/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:38:38 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/11 16:28:36 by hboudar          ###   ########.fr       */
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

void	sprite_animation(t_cube *cube, t_animation *sprite)
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

void	render_weapons(mlx_image_t *image, mlx_texture_t *picture)
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

void	draw_sprite(t_cube *cube, t_animation *anim, int w, int h)
{
	anim->start_x = 245 + w;
	anim->start_y = h + 10;
	anim->s_x = 0;
	anim->s_y = 0;
	while (anim->s_y < anim->sprite[anim->i]->height
		&& anim->s_y + anim->start_y < HEIGHT)
	{
		anim->s_x = 0;
		while (anim->s_x < anim->sprite[anim->i]->width
			&& anim->s_x + anim->start_x < WIDTH)
		{
			anim->color = get_pixel(anim->sprite[anim->i],
					anim->s_x, anim->s_y);
			if (((anim->color >> 24) & 0xFF) != 0)
				mlx_put_pixel(cube->image, anim->start_x + anim->s_x,
					anim->start_y + anim->s_y, anim->color);
			anim->s_x++;
		}
		anim->s_y++;
	}
}
