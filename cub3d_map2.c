/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:01:28 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/29 15:13:56 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_elem(char **map, t_cube *cube)
{
    int x;
    int y;
    int count;

    count = 0;
    x = 0;
    while (map[x])
    {
        y = 0;  
        while (map[x][y])
        {
            if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != 'N'
                && map[x][y] != 'S' && map[x][y] != 'W' && map[x][y] != 'E'
                    && map[x][y] != ' ')
                return (0);
            else if (map[x][y] == 'N' || map[x][y] == 'S'
                || map[x][y] == 'W' || map[x][y] == 'E')
                count++;
            y++;
        }
        (y > cube->width) && (cube->width = y);
        x++;
    }
    cube->height = x;
    return (count);
}

int just_space(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            return 0;
        i++;
    }
    return 1;
}

int check_map(char **map, int x, int y)
{
    while (map[x + 1] != NULL) 
    {
        y = 0;  
        if (ft_strlen(map[x]) == 0 || just_space(map[x]))
            return (0);
        while (map[x][y])
        {
            if ((map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'W' || map[x][y] == 'E') \
                && (map[x + 1][y] && map[x - 1][y] && map[x][y + 1] && map[x][y - 1]))
            {
                if (map[x + 1][y] != '0' && map[x + 1][y] != '1' && map[x + 1][y] != 'N' && map[x + 1][y] != 'S' && map[x + 1][y] != 'W' && map[x + 1][y] != 'E')
                    return (0);
                if (map[x - 1][y] != '0' && map[x - 1][y] != '1' && map[x - 1][y] != 'N' && map[x - 1][y] != 'S' && map[x - 1][y] != 'W' && map[x - 1][y] != 'E')
                    return (0);
                if (map[x][y + 1] != '0' && map[x][y + 1] != '1' && map[x][y + 1] != 'N' && map[x][y + 1] != 'S' && map[x][y + 1] != 'W' && map[x][y + 1] != 'E')
                    return (0);
                if (map[x][y - 1] != '0' && map[x][y - 1] != '1' && map[x][y - 1] != 'N' && map[x][y - 1] != 'S' && map[x][y - 1] != 'W' && map[x][y - 1] != 'E')
                    return (0);
            }
            else if (map[x][y] == '0' || map[x][y] == 'N' \
                || map[x][y] == 'S' || map[x][y] == 'W' || map[x][y] == 'E')
                return (0);
            y++;
        }
        x++;
    }
    return (x);
}

int parse_mape2(t_cube *cube)
{
    char *tmp;
    int r;

    r = check_elem(cube->map, cube);
    if (!r || r != 1)
        return (1);
    r = check_map(cube->map, 1 , 0);
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
