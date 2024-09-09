/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:43:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/27 12:22:15 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	costum_atoi(char *str, int *index)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res > 255 || res < 0)
		{
			*index += i;
			return (-1);
		}
	}
	*index += i;
	return (res);
}

static int	*get_rgb(t_cube *cube, char **tmp)
{
	int	f;
	int	j;
	int	i;
	int	*rgb;

	(1) && (i = 0, f = 0, j = 0, rgb = malloc(sizeof(int) * 3));
	if (!rgb)
		ft_eraser(cube, tmp, NULL, "Error : malloc failed\n");
	while (tmp[1][i])
	{
		if (tmp[1][i] <= '9' && tmp[1][i] >= '0')
			rgb[j++] = costum_atoi(tmp[1] + i, &i);
		else if (tmp[1][i] == ',')
			(1) && (f++, i++);
		else
			ft_eraser(cube, tmp, rgb, "Error : Wrong RGB format\n");
	}
	if (f != 2 || rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
		ft_eraser(cube, tmp, rgb, "Error : Wrong RGB format\n");
	return (rgb);
}

void	get_element(t_cube *cube, char *str, char mode)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(str, ' ');
	if (!tmp)
		ft_eraser(cube, NULL, NULL, "Error : ft_split failed 1\n");
	if (tmp[0] != NULL && tmp[1] != NULL && tmp[2] == NULL)
	{
		(mode == 'N') && (cube->textures.no = ft_strdup(tmp[1]));
		(mode == 'S') && (cube->textures.so = ft_strdup(tmp[1]));
		(mode == 'W') && (cube->textures.we = ft_strdup(tmp[1]));
		(mode == 'E') && (cube->textures.ea = ft_strdup(tmp[1]));
		(mode == 'F') && (cube->textures.f = get_rgb(cube, tmp));
		(mode == 'C') && (cube->textures.c = get_rgb(cube, tmp));
		cube->textures.flag++;
	}
	else
		ft_eraser(cube, tmp, NULL, "Error : Wrong format\n");
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}
