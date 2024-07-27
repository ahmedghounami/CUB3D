#include "cub3d.h"


int count_elem(char **map)
{
    int x = 0;
    int y = 0;
    int count = 0;
    while (map[x])
    {
        y = 0;  
        while (map[x][y])
        {
            if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'W' || map[x][y] == 'E')
                count++;
            y++;
        }
        x++;
    }
    if (count != 1)
        return 1;
    return 0;
}
int check_map(char **map)
{
    int x = 0;
    int y = 0;
    while (map[x])
    {
        y = 0;  
        if (ft_strlen(map[x]) == 0)
            return 1;
        while (map[x][y])
        {
            if ((map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'W' || map[x][y] == 'E') \
                && (map[x + 1][y] && map[x - 1][y] && map[x][y + 1] && map[x][y - 1]))
            {
                if (map[x + 1][y] != '0' && map[x + 1][y] != '1' && map[x + 1][y] != 'N' && map[x + 1][y] != 'S' && map[x + 1][y] != 'W' && map[x + 1][y] != 'E')
                    return 1;
                if (map[x - 1][y] != '0' && map[x - 1][y] != '1' && map[x - 1][y] != 'N' && map[x - 1][y] != 'S' && map[x - 1][y] != 'W' && map[x - 1][y] != 'E')
                    return 1;
                if (map[x][y + 1] != '0' && map[x][y + 1] != '1' && map[x][y + 1] != 'N' && map[x][y + 1] != 'S' && map[x][y + 1] != 'W' && map[x][y + 1] != 'E')
                    return 1;
                if (map[x][y - 1] != '0' && map[x][y - 1] != '1' && map[x][y - 1] != 'N' && map[x][y - 1] != 'S' && map[x][y - 1] != 'W' && map[x][y - 1] != 'E')
                    return 1;
            }
            else if (map[x][y] == '0' || map[x][y] == 'N' \
                || map[x][y] == 'S' || map[x][y] == 'W' || map[x][y] == 'E')
                return 1;
            y++;
        }
        x++;
    }
    return 0;
}
int parse_mape_2(t_cube *cube)
{
    int r  = 0;
    r = count_elem(cube->map);
    if (r == 0)
        r = check_map(cube->map);
    return r;
}