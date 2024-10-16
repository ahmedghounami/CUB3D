/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:01:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/27 10:59:41 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	take_map(t_pars *pars, int i, int j, int k)
{
	while (pars->fd_file[i])
	{
		if (pars->fd_file[i] == 'N' || pars->fd_file[i] == 'S' || \
			pars->fd_file[i] == 'W' || pars->fd_file[i] == 'E' || \
			pars->fd_file[i] == 'F' || pars->fd_file[i] == 'C')
			i += skip_line(pars, i, 1);
		else
		{
			k = 0;
			pars->map[j] = malloc(sizeof(char)
					* (skip_line(pars, i, 0) + 1));
			while (pars->fd_file[i] && pars->fd_file[i] != '\n')
				(1) && (pars->map[j][k] = pars->fd_file[i], (i++, k++));
			if (pars->fd_file[i] == '\n')
				i++;
			pars->map[j][k] = '\0';
			j++;
		}
	}
	pars->map[j] = NULL;
}

static int	parse_mape2(t_cube *cube, t_pars *pars)
{
	char	*tmp;
	int		r;

	r = check_elem(pars->map, cube);
	add_spaces(cube, NULL, 0, 0);
	if (!r || r != 1)
		return (1);
	r = check_map(pars->map, 1, 0);
	if (r)
	{
		tmp = ft_strtrim(pars->map[r], "1 ");
		if ((tmp && tmp[0] != '\0') || !ft_strlen(pars->map[r]))
			ft_eraser(cube, NULL, (void *)tmp, "Error : invalid map\n");
		(tmp) && (free (tmp), tmp = NULL);
	}
	else
		return (1);
	return (0);
}

static void	parse_map(t_cube *cube, t_pars *pars, char *tmp1, char **tmp2)
{
	int	i;
	int	j;

	(1) && (j = 0, i = 6);
	tmp1 = ft_strtrim(pars->file[i], "1 ");
	if (!ft_strchr(pars->file[i], '1') || (tmp1 && tmp1[0] != '\0'))
		ft_eraser(cube, NULL, (void *)tmp1, "Error : invalid map\n");
	(tmp1) && (free (tmp1), tmp1 = NULL);
	pars->map = (char **)malloc(sizeof(char *)
			* (pars->len_file - i + 1));
	if (!pars->map)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	take_map(pars, 0, 0, 0);
	i = 0;
	while (ft_strlen(pars->map[i]) == 0 || skip_space(pars->map[i], 1))
		i++;
	tmp2 = (char **)malloc(sizeof(char *) * ((pars->len_file - 6 - i) + 1));
	if (!tmp2)
		ft_eraser(cube, NULL, NULL, "Error : malloc failed\n");
	while (pars->map[i])
		(1) && (tmp2[j] = ft_strdup(pars->map[i]), i++, j++);
	(1) && (tmp2[j] = NULL, i = -1);
	while (pars->map[++i])
		(1) && (free(pars->map[i]), pars->map[i] = NULL);
	(1) && (free(pars->map), pars->map = NULL, pars->map = tmp2);
}

void	parse_textures(t_cube *cube, t_pars *pars, t_win *window)
{
	int	i;

	i = 0;
	(!pars->file) && (ft_error("Error : ft_split failed\n"));
	while (pars->file[i] && i < 7)
	{
		if (!ft_strncmp(pars->file[i], "NO ", 3))
			get_element(cube, pars->file[i], 'N');
		else if (!ft_strncmp(pars->file[i], "SO ", 3))
			get_element(cube, pars->file[i], 'S');
		else if (!ft_strncmp(pars->file[i], "WE ", 3))
			get_element(cube, pars->file[i], 'W');
		else if (!ft_strncmp(pars->file[i], "EA ", 3))
			get_element(cube, pars->file[i], 'E');
		else if (!ft_strncmp(pars->file[i], "F ", 2))
			get_element(cube, pars->file[i], 'F');
		else if (!ft_strncmp(pars->file[i], "C ", 2))
			get_element(cube, pars->file[i], 'C');
		i++;
	}
	if (window->flag != 6)
		ft_eraser(cube, NULL, NULL, "Error : an element is missing\n");
	else if (!window->no || !window->so || !window->we || !window->ea
		|| !window->f || !window->c)
		ft_eraser(cube, NULL, NULL, "Error : an element is missing\n");
}

void	is_map_valid(int argc, char *argv[], t_cube *cube)
{
	char	*line;
	char	*tmp;

	check_map_name(argc, argv[1], 0);
	initialize_list(cube, argv[1]);
	tmp = ft_strdup("");
	line = get_next_line(cube->pars.fd);
	while (line)
	{
		tmp = ft_strjoin(tmp, line);
		line = get_next_line(cube->pars.fd);
		cube->pars.len_file++;
	}
	cube->pars.fd_file = tmp;
	cube->pars.file = ft_split(tmp, '\n');
	if (!cube->pars.file)
		ft_eraser(cube, NULL,
			(void *)tmp, "Error : ft_split failed\n");
	parse_textures(cube, &cube->pars, &cube->window);
	parse_map(cube, &cube->pars, NULL, NULL);
	if (parse_mape2(cube, &cube->pars))
		ft_eraser(cube, NULL, NULL, "Error : invalid map\n");
	(cube->pars.fd) && (close(cube->pars.fd), cube->pars.fd = 0);
}
