/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/26 13:07:43 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_file(t_cube *cube)
{
	int i;

	i = 0;
	while (cube->file[i])
	{
		printf("%s\n", cube->file[i]);
		i++;
	}
	printf("North : %s\n", cube->texture.north);
	printf("South : %s\n", cube->texture.south);
	printf("West : %s\n", cube->texture.west);
	printf("East : %s\n", cube->texture.east);
	
	
}

int    key_hook(int keycode, void *param)
{
	(void)param;
    if (keycode == 53)
        exit(0);
    return (0);
}

void	f(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_cube	cube;

	// atexit(f);
	is_map_valid(argc, argv, &cube);
	cube.mlx = mlx_init();
	cube.mlx_win = mlx_new_window(cube.mlx, 1920, 1080, "Hello world!");
    mlx_key_hook(cube.mlx_win, key_hook, (void *)0);
	mlx_loop(cube.mlx);
	
}
