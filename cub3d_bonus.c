/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:21:43 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/30 16:49:27 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d_bonus.h"

int	main(int argc, char *argv[])
{
	t_cube	cube;

	is_map_valid(argc, argv, &cube);
	init_exec(&cube, &cube.player);
	return (EXIT_SUCCESS);
}
