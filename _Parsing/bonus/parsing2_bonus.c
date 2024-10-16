/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:01:28 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/30 17:43:02 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	skip_space(char *str, int mode)
{
	int	i;

	i = 0;
	if (!mode)
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	else
	{
		while (str[i])
		{
			if (str[i] != ' ')
				return (0);
			i++;
		}
		return (1);
	}
	return (i);
}

int	skip_line(t_pars *pars, int i, int mode)
{
	if (mode)
	{
		mode = 0;
		while (pars->fd_file[i] && pars->fd_file[i] != '\n')
			(1) && (i++, mode++);
		if (pars->fd_file[i] == '\n')
			(1) && (i++, mode++);
	}
	else
	{
		while (pars->fd_file[i] && pars->fd_file[i] != '\n')
		{
			i++;
			mode++;
		}
	}
	return (mode);
}

static int	next_check(char **map, int x, int y)
{
	if (map[x + 1][y] != '0' && map[x + 1][y] != '1' &&
		map[x + 1][y] != 'N' && map[x + 1][y] != 'S' &&
		map[x + 1][y] != 'W' && map[x + 1][y] != 'E' &&
		map[x + 1][y] != 'C')
		return (0);
	if (map[x - 1][y] != '0' && map[x - 1][y] != '1' &&
		map[x - 1][y] != 'N' && map[x - 1][y] != 'S' &&
		map[x - 1][y] != 'W' && map[x - 1][y] != 'E' &&
		map[x - 1][y] != 'C')
		return (0);
	if (map[x][y + 1] != '0' && map[x][y + 1] != '1' &&
		map[x][y + 1] != 'N' && map[x][y + 1] != 'S' &&
		map[x][y + 1] != 'W' && map[x][y + 1] != 'E' &&
		map[x][y + 1] != 'C')
		return (0);
	if (map[x][y - 1] != '0' && map[x][y - 1] != '1' &&
		map[x][y - 1] != 'N' && map[x][y - 1] != 'S' &&
		map[x][y - 1] != 'W' && map[x][y - 1] != 'E' &&
		map[x][y - 1] != 'C')
		return (0);
	return (1);
}

int	check_map(char **map, int x, int y)
{
	while (map[x + 1] != NULL)
	{
		y = 0;
		if (ft_strlen(map[x]) == 0 || skip_space(map[x], 1))
			return (0);
		while (map[x][y])
		{
			if ((map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S' ||
					map[x][y] == 'W' || map[x][y] == 'E' || map[x][y] == 'C')
					&& (map[x + 1][y] && map[x - 1][y] &&
						map[x][y + 1] && map[x][y - 1]))
			{
				if (!next_check(map, x, y))
					return (0);
			}
			else if (map[x][y] == '0' || map[x][y] == 'N' ||
					map[x][y] == 'S' || map[x][y] == 'W' ||
					map[x][y] == 'E' || map[x][y] == 'C')
				return (0);
			y++;
		}
		x++;
	}
	return (x);
}

int	check_elem(char **map, t_cube *cube)
{
	int	count;
	int	x;
	int	y;

	(1) && (count = 0, y = 0);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'N'
					&& map[y][x] != 'S' && map[y][x] != 'W' && map[y][x] != 'E'
					&& map[y][x] != ' ' && map[y][x] != 'C')
				return (0);
			else if (map[y][x] == 'N' || map[y][x] == 'S'
					|| map[y][x] == 'W' || map[y][x] == 'E')
				(1) && (count++, cube->player.x = x, cube->player.y = y,
					cube->player.way = map[y][x]);
			x++;
		}
		(x > cube->window.width) && (cube->window.width = x);
		y++;
	}
	cube->window.height = y;
	return (count);
}
