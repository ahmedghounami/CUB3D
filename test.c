#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int count_elem(char **file)
{
    int x = 0;
    int y = 0;
    int count = 0;
    while (file[x])
    {
        y = 0;  
        while (file[x][y])
        {
            if (file[x][y] == 'N' || file[x][y] == 'S' || file[x][y] == 'W' || file[x][y] == 'E')
                count++;
            y++;
        }
        x++;
    }
    if (count != 1)
        return 1;
    return 0;
}
int check_map(char **file)
{
    int x = 0;
    int y = 0;
    while (file[x])
    {
        y = 0;  
        if (strlen(file[x]) == 0)
            return 1;
        while (file[x][y])
        {
            if ((file[x][y] == '0' || file[x][y] == 'N' || file[x][y] == 'S' || file[x][y] == 'W' || file[x][y] == 'E') \
                && (file[x + 1][y] && file[x - 1][y] && file[x][y + 1] && file[x][y - 1]))
            {
                if (file[x + 1][y] != '0' && file[x + 1][y] != '1' && file[x + 1][y] != 'N')
                    return 1;
                if (file[x - 1][y] != '0' && file[x - 1][y] != '1' && file[x - 1][y] != 'N')
                    return 1;
                if (file[x][y + 1] != '0' && file[x][y + 1] != '1' && file[x][y + 1] != 'N')
                    return 1;
                if (file[x][y - 1] != '0' && file[x][y - 1] != '1' && file[x][y - 1] != 'N')
                    return 1;
            }
            else if (file[x][y] == '0' || file[x][y] == 'N' \
                || file[x][y] == 'S' || file[x][y] == 'W' || file[x][y] == 'E')
                return 1;
            y++;
        }
        x++;
    }
    return 0;
}

int main()
{
    char **file;
    int i;

    // Allocate memory for 14 lines
    file = malloc(15 * sizeof(char *));
    if (file == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Initialize each line of the map
    
    file[0] = strdup("        1 1 1");
    file[1] = strdup("    1010101       1111");
    file[2] = strdup("1111100011011111111111111");
    file[3] = strdup("1000000000110000000000001    1");
    file[4] = strdup("1011000001110000000000001   101");
    file[5] = strdup("1001000000000000000000001111111111");
    file[6] = strdup("1111111111111111111111111111111111");
    file[7] = strdup("1");
    file[8] = strdup("1111111111111111111111111111111111");
    file[9] = strdup("11110111111111011101N10010001");
    file[10] =strdup( "11000000111101011100000010001");
    file[11] =strdup( "1000000001 1000001100000010001");
    file[12] =strdup( "10000000001000001101010011001");
    file[13] =strdup( "1111111111111111111111111 11");
    file[14] = NULL;
    int r  = 0;
    r = count_elem(file);
    if (r == 0)
        r = check_map(file);
    if (r == 1)
        printf("Invalid map\n");
    else
        printf("Valid map\n");
    // Print each line
    
}


