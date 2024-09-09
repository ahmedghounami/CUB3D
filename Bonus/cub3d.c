/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:03:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/06 12:13:45 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

void	init_exec(t_cube *cube)
{
	cube->mlx = mlx_init((int32_t)WIDTH, \
		(int32_t)HEIGHT, "MLX42", false);
	cube->image = mlx_new_image(cube->mlx, \
		(int32_t)WIDTH, (int32_t)HEIGHT);
	get_player_position(cube);
	cube->wall_1 = mlx_load_png(cube->textures.no);
	cube->wall_2 = mlx_load_png(cube->textures.so);
	cube->wall_3 = mlx_load_png(cube->textures.ea);
	cube->wall_4 = mlx_load_png(cube->textures.we);
	cube->weapon = mlx_load_png("weapon/1.png");
	cube->door = mlx_load_png("textures/door.png");
	if (!cube->wall_1 || !cube->wall_2 || !cube->weapon \
		|| !cube->wall_3 || !cube->wall_4 || !cube->door)
		ft_error("Error : Texture not found\n");
	(cube->player_init_dir == N) && (cube->player_angle = 0);
	(cube->player_init_dir == S) && (cube->player_angle = M_PI);
	(cube->player_init_dir == W) && (cube->player_angle = 3 * M_PI_2);
	(cube->player_init_dir == E) && (cube->player_angle = M_PI_2);
	cube->flag_door = 0;
	cube->sprite_count = 0;
	cube->init_screen = 0;
}

void weapon_shoot(t_cube *cube)
{
    static int shooting = 0;

    if (mlx_is_key_down(cube->mlx, MLX_KEY_SPACE))
    {
        if (shooting == 0)
        {
            cube->weapon = mlx_load_png("weapon/2.png");
            shooting = 1;
        }
        else if (shooting == 1)
        {
            cube->weapon = mlx_load_png("weapon/3.png");
            shooting = 2;
        }
		else if (shooting == 2)
		{
			cube->weapon = mlx_load_png("weapon/1.png");
			shooting = 0;
		}
    }
	else
	{
		cube->weapon = mlx_load_png("weapon/1.png");
		shooting = 0;
	}
}

void draw_background(t_cube *cube)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(cube->image, x, y,  ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
}

void start_image(t_cube *cube)
{
	draw_background(cube);
    uint32_t start_x;
    uint32_t start_y;
    uint32_t window_x;
    uint32_t window_y;
    uint32_t color;
    int offset_x = (WIDTH - cube->start_screen->width) / 2;
    int offset_y = (HEIGHT - cube->start_screen->height) / 2;
    start_y = 0;
    while (start_y < cube->start_screen->height)
    {
        start_x = 0;
        while (start_x < cube->start_screen->width)
        {
            color = get_pixel(cube->start_screen, start_x, start_y);
            window_x = start_x + offset_x;
            window_y = start_y + offset_y;
                mlx_put_pixel(cube->image, window_x, window_y, color);

            start_x++;
        }
        start_y++;
    }
}


int	main(int argc, char **argv)
{
	t_cube	cube;
	int		error;

	error = 0;
	is_map_valid(argc, argv, &cube);
	parse_textures(&cube, 0);
	parse_mape(&cube, NULL, NULL, 6);
	error = parse_mape2(&cube);
	if (error)
		ft_error("Error : Map is invalid 2\n");
	init_exec(&cube);
	mlx_loop_hook(cube.mlx, ft_randomize, &cube);
	mlx_loop(cube.mlx);
	return (EXIT_SUCCESS);
}
