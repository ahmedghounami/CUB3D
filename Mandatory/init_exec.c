/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:17:23 by aghounam          #+#    #+#             */
/*   Updated: 2024/08/30 10:25:50 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	ft_randomize(void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	ft_hook(cube);
	// ft_mouse_hook(cube);
	// weapon_shoot(cube);
	mlx_delete_image(cube->mlx, cube->image);
	cube->image = mlx_new_image(cube->mlx, (int32_t)WIDTH, (int32_t)HEIGHT);
	ray_casting(cube, cube->image);
	// draw_mini_map(cube, cube->image);
	// rander_weapons(cube->image, cube->weapon);
	// sprite_animation(cube, cube->image);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
}
