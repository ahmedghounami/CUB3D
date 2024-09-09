/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:01:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/05 20:47:46 by aghounam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	just_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	parse_mape(t_cube *cube, char *tmp1, char **tmp2, int i)
{
	int	j;

	j = 0;
	tmp1 = ft_strtrim(cube->file[i], "1 ");
	if (!ft_strchr(cube->file[i], '1') || (tmp1 && tmp1[0] != '\0'))
		ft_eraser(cube, NULL, (void *)tmp1, "Error : invalid map\n");
	(tmp1) && (free (tmp1), tmp1 = NULL);
	cube->map = (char **)malloc(sizeof(char *) * (cube->file_len - i + 1));
	if (!cube->map)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	take_map(cube, 0, 0, 0);
	i = 0;
	while (ft_strlen(cube->map[i]) == 0 || just_space(cube->map[i]))
		i++;
	tmp2 = (char **)malloc(sizeof(char *) * ((cube->file_len - 6 - i) + 1));
	if (!tmp2)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	while (cube->map[i])
		(1) && (tmp2[j] = ft_strdup(cube->map[i]), i++, j++);
	tmp2[j] = NULL;
	free(cube->map);
	cube->map = tmp2;
}

void	parse_textures(t_cube *cube, int i)
{
	if (!cube->file)
		ft_error("Error : ft_split failed\n");
	while (cube->file[i] && i < 7)
	{
		if (!ft_strncmp(cube->file[i], "NO ", 3))
			get_element(cube, cube->file[i]);
		else if (!ft_strncmp(cube->file[i], "SO ", 3))
			get_element(cube, cube->file[i]);
		else if (!ft_strncmp(cube->file[i], "WE ", 3))
			get_element(cube, cube->file[i]);
		else if (!ft_strncmp(cube->file[i], "EA ", 3))
			get_element(cube, cube->file[i]);
		else if (!ft_strncmp(cube->file[i], "F ", 2))
			get_element(cube, cube->file[i]);
		else if (!ft_strncmp(cube->file[i], "C ", 2))
			get_element(cube, cube->file[i]);
		i++;
	}
	if (cube->textures.flag != 6)
		ft_error("Error : elements are not valid\n");
	else if (!cube->textures.no || !cube->textures.so || !cube->textures.we
		|| !cube->textures.ea || !cube->textures.f || !cube->textures.c)
		ft_error("Error : an element is missing\n");
}

static void	check_name(int argc, char *s, int i)
{
	if (s == NULL)
		ft_error("Error : No file\n");
	else if (argc > 2)
		ft_error("Error : Too many arguments\n");
	while (s[i])
		i++;
	if (i < 4 || s[i - 1] != 'b' || s[i - 2] != 'u' \
		|| s[i - 3] != 'c' || s[i - 4] != '.')
		ft_error("Error : Wrong file extension\n");
	else if (access(s, F_OK) == -1)
		ft_error("Error : File doesn't exist\n");
	else if (access(s, R_OK) == -1)
		ft_error("Error : File is not readable\n");
}

void	is_map_valid(int argc, char *argv[], t_cube *cube)
{
	char	*line;
	char	*tmp;

	check_name(argc, argv[1], 0);
	cube->fd = open(argv[1], O_RDONLY);
	if (cube->fd == -1)
		ft_error("Error : open failed\n");
	ft_init_texture(cube);
	(1) && (line = get_next_line(cube->fd), tmp = ft_strdup(""));
	while (line)
	{
		cube->file_len++;
		tmp = ft_strjoin(tmp, line);
		line = get_next_line(cube->fd);
	}
	cube->fd_file = tmp;
	cube->file = ft_split(tmp, '\n');
	if (!cube->file)
		ft_eraser(cube, NULL, (void *)tmp, "Error : ft_split failed\n");
}
