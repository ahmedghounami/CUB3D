/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:17:20 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/27 14:37:50 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_render_pixel(int32_t x, int32_t y, int32_t color, mlx_image_t *image)
{
	double	i;
	double	j;

	i = 0;
	j = 0;
	while (i < MINI_MAP_T)
	{
		j = 0;
		while (j < MINI_MAP_T)
		{
			mlx_put_pixel(image, x * MINI_MAP_T + i + 1, \
				y * MINI_MAP_T + j + 1, color);
			j++;
		}
		i++;
	}
}

void	draw_utils(t_cube *cube, mlx_image_t *image, double angle)
{
	int	j;
	int	x;
	int	y;

	j = 0;
	while (j < cube->true_distance)
	{
		x = cube->yplayer_x_pixel + j * cos(angle);
		y = cube->player_y_pixel + j * sin(angle);
		if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
			break ;
		mlx_put_pixel(image, x, y, ft_pixel(0xFF, 0x00, 0x00, 0xFF));
		j++;
	}
}

void	rander_map(t_cube *cube, mlx_image_t *image)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (cube->map[x])
	{
		y = 0;
		while (cube->map[x][y])
		{
			if (cube->map[x][y] == '1')
				ft_render_pixel(y, x, ft_pixel(0xFF, 0xFF, 0xFF, \
				0xFF), image);
			else if (cube->map[x][y] == '0' || cube->map[x][y] == ' ')
				ft_render_pixel(y, x, ft_pixel(0x00, 0x00, 0x00, \
				0xFF), image);
			else if (cube->map[x][y] == 'W' || cube->map[x][y] == 'N' || \
					cube->map[x][y] == 'S' || cube->map[x][y] == 'E')
				ft_render_pixel(y, x, ft_pixel(0x00, 0x00, 0x00, \
				0xFF), image);
			y++;
		}
		x++;
	}
}
