/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:26:27 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/27 12:31:15 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg)
{
	int	i;

	i = -1;
	(cube->textures.no) && (free(cube->textures.no), cube->textures.no = NULL);
	(cube->textures.so) && (free(cube->textures.so), cube->textures.so = NULL);
	(cube->textures.we) && (free(cube->textures.we), cube->textures.we = NULL);
	(cube->textures.ea) && (free(cube->textures.ea), cube->textures.ea = NULL);
	(cube->textures.f) && (free(cube->textures.f), cube->textures.f = NULL);
	(cube->textures.c) && (free(cube->textures.c), cube->textures.c = NULL);
	while (tmp && tmp[++i])
		free(tmp[i]);
	(tmp) && (free(tmp), tmp = NULL);
	(rgb) && (free(rgb), rgb = NULL);
	ft_error(msg);
}

void	ft_init_texture(t_cube *cube)
{
	cube->map_len = 0;
	cube->file_len = 0;
	cube->textures.flag = 0;
	cube->height = 0;
	cube->width = 0;
	cube->file = NULL;
	cube->map = NULL;
	cube->textures.no = NULL;
	cube->textures.so = NULL;
	cube->textures.we = NULL;
	cube->textures.ea = NULL;
	cube->textures.f = NULL;
	cube->textures.c = NULL;
}

int	skip_line(t_cube *cube, int i, int mode)
{
	if (mode)
	{
		mode = 0;
		while (cube->fd_file[i] && cube->fd_file[i] != '\n')
			(1) && (i++, mode++);
		if (cube->fd_file[i] == '\n')
			(1) && (i++, mode++);
	}
	else
	{
		while (cube->fd_file[i] && cube->fd_file[i] != '\n')
		{
			i++;
			mode++;
		}
	}
	return (mode);
}

void	take_map(t_cube *cube, int i, int j, int k)
{
	while (cube->fd_file[i])
	{
		if (cube->fd_file[i] == 'N' || cube->fd_file[i] == 'S' || \
			cube->fd_file[i] == 'W' || cube->fd_file[i] == 'E' || \
			cube->fd_file[i] == 'F' || cube->fd_file[i] == 'C')
			i += skip_line(cube, i, 1);
		else
		{
			k = 0;
			cube->map[j] = malloc(sizeof(char) * (skip_line(cube, i, 0) + 1));
			while (cube->fd_file[i] && cube->fd_file[i] != '\n')
				(1) && (cube->map[j][k] = cube->fd_file[i], (i++, k++));
			if (cube->fd_file[i] == '\n')
				i++;
			cube->map[j][k] = '\0';
			j++;
		}
	}
	cube->map[j] = NULL;
}
