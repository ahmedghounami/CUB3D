/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:01:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/26 18:19:32 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "lib/libft.h"
#include <stdlib.h>
// #include <cstdio>

void    ft_init_texture(t_cube *cube)
{
    cube->map_len = 0;
    cube->file_len = 0;
    cube->texture.flag = 0;
    cube->file = NULL;
    cube->map = NULL;
    cube->texture.north = NULL;
    cube->texture.south = NULL;
    cube->texture.west = NULL;
    cube->texture.east = NULL;
    cube->texture.floor = NULL;
    cube->texture.ceiling = NULL;
    
}

static void check_name(int argc, char *str)
{
    int i;

    i = 0;
    if (str == NULL)
    {
        write(2, "Error : No file\n", 16);
        exit (EXIT_FAILURE);
    }
    else if (argc > 2)
    {
        write(2, "Error : Too many arguments\n", 28);
        exit (EXIT_FAILURE);
    }
    while (str[i])
        i++;
    if (i < 4 || str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || str[i - 4] != '.')
    {
        write(2, "Error : Wrong file extension\n", 29);
        exit (EXIT_FAILURE);
    }
    else if (access(str, F_OK) == -1)
    {
        write(2, "Error : File doesn't exist\n", 28);
        exit (EXIT_FAILURE);
    }
}

void    parse_textures(t_cube *cube, int i)
{
    if (!cube->file)
        ft_error("Error : ft_split failed\n");
    while (cube->file[i] && i < 7)
    {
        if (cube->file[i][0] == 'N' && cube->file[i][1] == 'O' && cube->file[i][2] == ' ')
            get_element(cube, cube->file[i], 'N');
        else if (cube->file[i][0] == 'S' && cube->file[i][1] == 'O' && cube->file[i][2] == ' ')
            get_element(cube, cube->file[i], 'S');
        else if (cube->file[i][0] == 'W' && cube->file[i][1] == 'E' && cube->file[i][2] == ' ')
            get_element(cube, cube->file[i], 'W');
        else if (cube->file[i][0] == 'E' && cube->file[i][1] == 'A' && cube->file[i][2] == ' ')
            get_element(cube, cube->file[i], 'E');
        else if (cube->file[i][0] == 'F' && cube->file[i][1] == ' ')
            get_element(cube, cube->file[i], 'F');
        else if (cube->file[i][0] == 'C' && cube->file[i][1] == ' ')
            get_element(cube, cube->file[i], 'C');
        i++;
    }
    if (cube->texture.flag != 6)
        ft_error("Error : elements are not valid\n");
    else if (!cube->texture.north || !cube->texture.south || !cube->texture.west
        || !cube->texture.east || !cube->texture.floor || !cube->texture.ceiling)
        ft_error("Error : an element is missing\n");
}

void    take_map(t_cube *cube, int i, int j, int k)
{
    while (cube->fd_file[i])
    {
        if (cube->fd_file[i] == 'N' || cube->fd_file[i] == 'S' || cube->fd_file[i] == 'W' \
            || cube->fd_file[i] == 'E' || cube->fd_file[i] == 'F' || cube->fd_file[i] == 'C')
            {
                while (cube->fd_file[i] != '\n')
                    i++;
                if (cube->fd_file[i] == '\n')
                    i++;
            }
        else
        {
            k = 0;
            cube->map[j] = malloc(sizeof(char) * (100));
            while (cube->fd_file[i] && cube->fd_file[i] != '\n')
                (cube->map[j][k] = cube->fd_file[i], (i++, k++));
            if (cube->fd_file[i] == '\n')
                i++;
            cube->map[j][k] = '\0';
            j++;
        }
    }
    cube->map[j] = NULL;
}

void    parse_mape(t_cube *cube)
{
    int i;

    i = 6;
    if (!cube->file[i] || !ft_strchr(cube->file[6], '1'))
        ft_eraser(cube, NULL, NULL, "Error : invalid map\n");
    printf("flie_len = %d\n", cube->file_len);
    printf("map_len = %d\n", cube->map_len);
    cube->map = malloc(sizeof(char *) * (cube->file_len + 1));
    if (!cube->map)
        ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
    take_map(cube, 0, 0, 0);
    i = 0;
    while (ft_strlen(cube->map[i]) == 0)
        i++;
    char **tmp = malloc(sizeof(char *) * (cube->file_len + 1));
    if (!tmp)
        ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
    int j = 0;
    while (cube->map[i])
    {
        tmp[j] = ft_strdup(cube->map[i]);
        i++;
        j++;
    }
    tmp[j] = NULL;
    free(cube->map);
    cube->map = tmp;
}
void	is_map_valid(int argc, char *argv[], t_cube *cube)
{
    char *line;
    char *tmp;

    check_name(argc, argv[1]);
    cube->fd = open(argv[1], O_RDONLY);
    if (cube->fd == -1)
    {
        write(2, "Error : Can't open the file\n", 29);
        exit (EXIT_FAILURE);
    }
    ft_init_texture(cube);
    (1) && (line = get_next_line(cube->fd), tmp = ft_strdup(""));
    while(line)
    {
        cube->file_len++;
        if (line[0] == '\n' || is_an_element(line))
            cube->map_len++;
        tmp = ft_strjoin(tmp, line);
        line = get_next_line(cube->fd);
    }
    cube->fd_file = tmp;
    cube->file = ft_split(tmp, '\n');
}
