/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/24 15:33:25 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_cube	cube;

	is_map_valid(argc, argv, &cube);
	init_exec(&cube, &cube.player);
	return (EXIT_SUCCESS);
}
