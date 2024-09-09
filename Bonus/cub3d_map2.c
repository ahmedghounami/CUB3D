/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:01:28 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/27 12:14:02 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_player_direction(char c, t_cube *cube)
{
	(c == 'W') && (cube->player_init_dir = W);
	(c == 'N') && (cube->player_init_dir = N);
	(c == 'S') && (cube->player_init_dir = S);
	(c == 'E') && (cube->player_init_dir = E);
}

int	check_elem(char **map, t_cube *cube)
{
	int	x;
	int	y;
	int	count;	

	count = 0;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			check_player_direction(map[x][y], cube);
			if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != 'N'
				&& map[x][y] != 'S' && map[x][y] != 'W' && map[x][y] != 'E'
					&& map[x][y] != ' ' && map[x][y] != 'D')
				return (0);
			else if (map[x][y] == 'N' || map[x][y] == 'S'
				|| map[x][y] == 'W' || map[x][y] == 'E')
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

int	next_check(char **map, int x, int y)
{
	if (map[x + 1][y] != '0' && map[x + 1][y] != '1' &&
		map[x + 1][y] != 'N' && map[x + 1][y] != 'S' &&
		map[x + 1][y] != 'W' && map[x + 1][y] != 'E' &&
		map[x + 1][y] != 'D')
		return (0);
	if (map[x - 1][y] != '0' && map[x - 1][y] != '1' &&
		map[x - 1][y] != 'N' && map[x - 1][y] != 'S' &&
		map[x - 1][y] != 'W' && map[x - 1][y] != 'E' &&
		map[x - 1][y] != 'D')
		return (0);
	if (map[x][y + 1] != '0' && map[x][y + 1] != '1' &&
		map[x][y + 1] != 'N' && map[x][y + 1] != 'S' &&
		map[x][y + 1] != 'W' && map[x][y + 1] != 'E' &&
		map[x][y + 1] != 'D')
		return (0);
	if (map[x][y - 1] != '0' && map[x][y - 1] != '1' &&
		map[x][y - 1] != 'N' && map[x][y - 1] != 'S' &&
		map[x][y - 1] != 'W' && map[x][y - 1] != 'E' &&
		map[x][y - 1] != 'D')
		return (0);
	return (1);
}

int	check_map(char **map, int x, int y)
{
	while (map[x + 1] != NULL)
	{
		y = 0;
		if (ft_strlen(map[x]) == 0 || just_space(map[x]))
			return (0);
		while (map[x][y])
		{
			if ((map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S' ||
				map[x][y] == 'W' || map[x][y] == 'E' || map[x][y] == 'D') \
				&& (map[x + 1][y] && map[x - 1][y] &&
					map[x][y + 1] && map[x][y - 1]))
			{
				if (!next_check(map, x, y))
					return (0);
			}
			else if (map[x][y] == '0' || map[x][y] == 'N' ||
					map[x][y] == 'S' || map[x][y] == 'W' ||
					map[x][y] == 'E' || map[x][y] == 'D')
				return (0);
			y++;
		}
		x++;
	}
	return (x);
}

int	parse_mape2(t_cube *cube)
{
	char	*tmp;
	int		r;

	r = check_elem(cube->map, cube);
	if (!r || r != 1)
		return (1);
	r = check_map(cube->map, 1, 0);
	if (r)
	{
		tmp = ft_strtrim(cube->map[r], "1 ");
		if ((tmp && tmp[0] != '\0') || !ft_strlen(cube->map[r]))
			ft_eraser(cube, NULL, (void *)tmp, "Error : invalid map\n");
		(tmp) && (free (tmp), tmp = NULL);
	}
	else
		return (1);
	return (0);
}
