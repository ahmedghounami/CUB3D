/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:53:17 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/10 14:50:52 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	index;

	index = (y * texture->width + x) * texture->bytes_per_pixel;
	return (ft_pixel(texture->pixels[index], texture->pixels[index + 1],
			texture->pixels[index + 2], texture->pixels[index + 3]));
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
