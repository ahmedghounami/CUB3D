/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:51 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/07 15:59:31 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	render_sky(t_cube *cube, t_exec *exec, t_player *player, t_win *win)
{
	uint32_t	color;

	exec->i = 0;
	while (exec->i < exec->walltop_pixel)
	{
		color = get_pixel(win->sky, exec->ray, exec->i);
		mlx_put_pixel(cube->image, exec->ray, exec->i, color);
		exec->i++;
	}
	(player->way == 'E') && (exec->tx
			= fmod(win->ray_intercept, TILE) * win->t1->width / TILE);
	(player->way == 'W') && (exec->tx
			= fmod(win->ray_intercept, TILE) * win->t2->width / TILE);
	(player->way == 'N') && (exec->tx
			= fmod(win->ray_intercept, TILE) * win->t3->width / TILE);
	(player->way == 'S') && (exec->tx
			= fmod(win->ray_intercept, TILE) * win->t4->width / TILE);
	(player->way == 'C') && (exec->tx
			= fmod(win->ray_intercept, TILE)
			* win->door->width / TILE);
}

void	render_wall(t_cube *cube, t_exec *exec, t_player *ply, t_win *win)
{
	while (exec->i < exec->wallbottom_pixel)
	{
		(ply->way == 'E') && (exec->ty = (exec->i - exec->walltop_pixel)
				* win->t1->height / exec->wallstripheight);
		(ply->way == 'E') && (exec->color
				= get_pixel(win->t1, exec->tx, exec->ty));
		(ply->way == 'W') && (exec->ty = (exec->i - exec->walltop_pixel)
				* win->t2->height / exec->wallstripheight);
		(ply->way == 'W') && (exec->color
				= get_pixel(win->t2, exec->tx, exec->ty));
		(ply->way == 'N') && (exec->ty = (exec->i - exec->walltop_pixel)
				* win->t3->height / exec->wallstripheight);
		(ply->way == 'N') && (exec->color
				= get_pixel(win->t3, exec->tx, exec->ty));
		(ply->way == 'S') && (exec->ty = (exec->i - exec->walltop_pixel)
				* win->t4->height / exec->wallstripheight);
		(ply->way == 'S') && (exec->color
				= get_pixel(win->t4, exec->tx, exec->ty));
		(ply->way == 'C') && (exec->ty = (exec->i - exec->walltop_pixel)
				* win->door->height / exec->wallstripheight);
		(ply->way == 'C') && (exec->color
				= get_pixel(win->door, exec->tx, exec->ty));
		mlx_put_pixel(cube->image, exec->ray, exec->i, exec->color);
		exec->i++;
	}
}

void	render_window(t_cube *cube, t_exec *exec, t_player *player, t_win *wind)
{
	exec->correct_distance = cube->player.true_distance
		* cos(cube->player.rotation_angle - exec->ray_angle);
	exec->wallstripheight = (TILE / exec->correct_distance)
		* PROJECT_PLANE;
	exec->walltop_pixel = ((double)HEIGHT / 2) - (exec->wallstripheight / 2);
	exec->wallbottom_pixel = ((double)HEIGHT / 2) + (exec->wallstripheight / 2);
	if (exec->wallbottom_pixel > HEIGHT)
		exec->wallbottom_pixel = HEIGHT;
	if (exec->walltop_pixel < 0)
		exec->walltop_pixel = 0;
	if (exec->wallstripheight >= HEIGHT)
		exec->walltop_pixel -= (exec->wallstripheight - HEIGHT) / 2;
	render_sky(cube, exec, player, wind);
	render_wall(cube, exec, player, wind);
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

void	draw_sprite(t_cube *cube, t_sprite *sprite, int w, int h)
{
	sprite->start_x = 245 + w;
	sprite->start_y = h + 10;
	sprite->s_x = 0;
	sprite->s_y = 0;
	while (sprite->s_y < sprite->sprite[sprite->i]->height
		&& sprite->s_y + sprite->start_y < HEIGHT)
	{
		sprite->s_x = 0;
		while (sprite->s_x < sprite->sprite[sprite->i]->width
			&& sprite->s_x + sprite->start_x < WIDTH)
		{
			sprite->color = get_pixel(sprite->sprite[sprite->i],
					sprite->s_x, sprite->s_y);
			if (((sprite->color >> 24) & 0xFF) != 0)
				mlx_put_pixel(cube->image, sprite->start_x + sprite->s_x,
					sprite->start_y + sprite->s_y, sprite->color);
			sprite->s_x++;
		}
		sprite->s_y++;
	}
}
