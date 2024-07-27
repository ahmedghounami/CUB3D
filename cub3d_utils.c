/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:43:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/26 18:16:58 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_eraser(t_cube *cube, char **tmp, int *rgb, char *msg)
{
    int i;
    
    i = -1;
    (cube->texture.north) && (free(cube->texture.north), cube->texture.north = NULL);
    (cube->texture.south) && (free(cube->texture.south), cube->texture.south = NULL);
    (cube->texture.west) && (free(cube->texture.west), cube->texture.west = NULL);
    (cube->texture.east) && (free(cube->texture.east), cube->texture.east = NULL);
    (cube->texture.floor) && (free(cube->texture.floor), cube->texture.floor = NULL);
    (cube->texture.ceiling) && (free(cube->texture.ceiling), cube->texture.ceiling = NULL);
    while (tmp && tmp[++i])
        free(tmp[i]);
    (tmp) && (free(tmp), tmp = NULL);
    (rgb) && (free(rgb), rgb = NULL);
    ft_error(msg);
}

int    costum_atoi(char *str, int *index)
{
    int res;
    int i;

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

int    *get_rgb(t_cube *cube, char **tmp)
{
    int f;
    int j;
    int i;
    int *rgb;

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

void    get_element(t_cube *cube, char *str, char mode)
{
    int i;
    char **tmp;

    i = 0;
    tmp = ft_split(str, ' ');
    if (!tmp)
        ft_eraser(cube, NULL, NULL, "Error : ft_split failed\n");
    if (tmp[0] != NULL && tmp[1] != NULL && tmp[2] == NULL)
    {
        (mode == 'N') && (cube->texture.north = ft_strdup(tmp[1]));
        (mode == 'S') && (cube->texture.south = ft_strdup(tmp[1]));
        (mode == 'W') && (cube->texture.west = ft_strdup(tmp[1]));
        (mode == 'E') && (cube->texture.east = ft_strdup(tmp[1]));
        (mode == 'F') && (cube->texture.floor = get_rgb(cube, tmp));
        (mode == 'C') && (cube->texture.ceiling = get_rgb(cube, tmp));
        cube->texture.flag++;
    }
    else
        ft_eraser(cube, tmp, NULL, "Error : Wrong format\n");
    while (tmp[i])
        free(tmp[i++]);
    free(tmp);
}

int is_an_element(char *str)
{
    if ((str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
        || (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
        || (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
        || (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
        || (str[0] == 'F' && str[1] == ' ')
        || (str[0] == 'C' && str[1] == ' '))
        return (1);
    return (0);
}
