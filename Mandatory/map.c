/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:17:20 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/30 12:58:30 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
// void	draw_utils(t_cube *cube, mlx_image_t *image, double angle)
// {
// 	int	j;
// 	int	x;
// 	int	y;

// 	j = 0;
// 	while (j < cube->true_distance)
// 	{
// 		x = cube->yplayer_x_pixel + j * cos(angle);
// 		y = cube->player_y_pixel + j * sin(angle);
// 		if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
// 			break ;
// 		mlx_put_pixel(image, x, y, ft_pixel(0xFF, 0x00, 0x00, 0xFF));
// 		j++;
// 	}
// }
