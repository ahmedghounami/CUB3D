/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:26:08 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/01 13:07:10 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	smallest_distance(t_cube *cube)
{
	double	distance_oriz;
	double	distance_vert;

	distance_oriz = sqrt(pow(cube->player.x - cube->player.orizontal_x, 2)
			+ pow(cube->player.y - cube->player.orizontal_y, 2));
	distance_vert = sqrt(pow(cube->player.x - cube->player.vertical_x, 2)
			+ pow(cube->player.y - cube->player.vertical_y, 2));
	if (distance_oriz < distance_vert)
	{
		cube->window.ray_intercept = cube->player.orizontal_x;
		if (cube->player.facing_up)
			cube->player.way = 'W';
		else if (cube->player.facing_down)
			cube->player.way = 'E';
		return (distance_oriz);
	}
	cube->window.ray_intercept = cube->player.vertical_y;
	if (cube->player.facing_left)
		cube->player.way = 'N';
	else if (cube->player.facing_right)
		cube->player.way = 'S';
	return (distance_vert);
}

static int	check_wall(double x, double y, t_cube *cube, t_win *window)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE);
	map_y = floor(y / TILE);
	if (map_x < 0 || map_x >= window->width
		|| map_y < 0 || map_y >= window->height)
		return (1);
	if ((int)ft_strlen(cube->pars.map[map_y]) <= map_x)
		return (1);
	if (cube->pars.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	get_oriz(t_cube *cube, double angle, double x_step, double y_step)
{
	double	y_intercept;
	double	x_intercept;

	y_intercept = floor(cube->player.y / TILE) * TILE;
	(cube->player.facing_down) && (y_intercept += TILE);
	x_intercept = cube->player.x + (y_intercept - cube->player.y) / tan(angle);
	(cube->player.facing_up) && (y_step *= -1);
	(cube->player.facing_right && x_step < 0) && (x_step *= -1);
	(cube->player.facing_left && x_step > 0) && (x_step *= -1);
	(cube->player.facing_up) && (y_intercept -= 0.0001);
	while (1)
	{
		if (check_wall(x_intercept, y_intercept, cube, &cube->window))
		{
			cube->player.orizontal_x = x_intercept;
			cube->player.orizontal_y = y_intercept;
			break ;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}
}

static void	get_vert(t_cube *cube, double angle, double x_step, double y_step)
{
	double	x_intercept;
	double	y_intercept;

	x_intercept = floor(cube->player.x / TILE) * TILE;
	(cube->player.facing_right) && (x_intercept += TILE);
	y_intercept = cube->player.y + (x_intercept - cube->player.x) * tan(angle);
	(cube->player.facing_left) && (x_step *= -1);
	(cube->player.facing_down && y_step < 0) && (y_step *= -1);
	(cube->player.facing_up && y_step > 0) && (y_step *= -1);
	(cube->player.facing_left) && (x_intercept -= 0.0001);
	while (1)
	{
		if (check_wall(x_intercept, y_intercept, cube, &cube->window))
		{
			cube->player.vertical_x = x_intercept;
			cube->player.vertical_y = y_intercept;
			break ;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}
}

void	ray_casting(t_cube *cube, t_player *player)
{
	double	ray_angle;
	int		ray;

	ray = -1;
	ray_angle = normalize_angle(cube->player.rotation_angle) - (FOV / 2);
	while (++ray < WIDTH)
	{
		player->facing_down = (ray_angle > 0 && ray_angle < M_PI);
		player->facing_up = !player->facing_down;
		player->facing_right = (ray_angle < 0.5 * M_PI
				|| ray_angle > 1.5 * M_PI);
		player->facing_left = !player->facing_right;
		ray_angle = normalize_angle(ray_angle);
		get_oriz(cube, ray_angle, TILE / tan(ray_angle), TILE);
		get_vert(cube, ray_angle, TILE, TILE * tan(ray_angle));
		player->true_distance = smallest_distance(cube);
		cube->exec.ray_angle = ray_angle;
		cube->exec.ray = ray;
		render_window(cube, &cube->exec, player, &cube->window);
		ray_angle += FOV / WIDTH;
		ray_angle = normalize_angle(ray_angle);
	}
}
