/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:43:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/05 17:01:32 by aghounam         ###   ########.fr       */
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

static int    *get_rgb(t_cube *cube, char **tmp,  int *rgb)
{
    int f;
    int j;
    int i;

    if (!tmp)
        ft_eraser(cube, NULL, NULL, "Error : ft_split failed 1\n");
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
    i = 0;
    while (tmp[i])
        free(tmp[i++]);
    free(tmp);
    return (rgb);
}

void    get_element(t_cube *cube, char  *element)
{
    if (element[0] == 'N' && element[1] == 'O')
        cube->textures.no = ft_substr(element, 3, ft_strlen(element) - 3);
    else if (element[0] == 'S' && element[1] == 'O')
        cube->textures.so = ft_substr(element, 3, ft_strlen(element) - 3);
    else if (element[0] == 'W' && element[1] == 'E')
        cube->textures.we = ft_substr(element, 3, ft_strlen(element) - 3);
    else if (element[0] == 'E' && element[1] == 'A')
        cube->textures.ea = ft_substr(element, 3, ft_strlen(element) - 3);
    else if (element[0] == 'F')
        cube->textures.f = get_rgb(cube, ft_split(element, ' '), NULL);
    else if (element[0] == 'C')
        cube->textures.c = get_rgb(cube, ft_split(element, ' '), NULL);
    else
        ft_eraser(cube, NULL, NULL, "Error : Wrong format\n");
    cube->textures.flag++;
}