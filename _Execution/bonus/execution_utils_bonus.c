/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:53:17 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/16 17:33:17 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

void	ft_pixel_to_image(mlx_image_t *image, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE - 1)
	{
		j = -1;
		while (++j < TILE - 1)
			mlx_put_pixel(image, x + i, y + j, color);
		i++;
	}
}

int	check_wall(double x, double y, t_cube *cube)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE);
	map_y = floor(y / TILE);
	if (map_x < 0 || map_x >= cube->window.width
		|| map_y < 0 || map_y >= cube->window.height)
		return (1);
	if (cube->exec.mode && cube->pars.map[map_y][map_x] == 'O')
	{
		cube->window.door_state = 1;
		cube->window.mid_ray_distance = sqrt(pow(cube->player.x - x, 2)
				+ pow(cube->player.y - y, 2));
		if (cube->window.mid_ray_distance < TILE * 1.5)
			cube->pars.map[map_y][map_x] = 'C';
		return (1);
	}
	if (cube->pars.map[map_y][map_x] == '1'
		|| cube->pars.map[map_y][map_x] == 'C')
		return (1);
	return (0);
}

int	get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	index;

	index = (y * texture->width + x) * texture->bytes_per_pixel;
	return (ft_pixel(texture->pixels[index], texture->pixels[index + 1],
			texture->pixels[index + 2], texture->pixels[index + 3]));
}
