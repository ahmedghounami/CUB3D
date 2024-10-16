/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:56:35 by hboudar           #+#    #+#             */
/*   Updated: 2024/10/13 17:36:43 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	ft_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	ft_eraser(t_cube *cube, void *tmp, int *rgb, char *msg)
{
	int		i;
	t_win	*window;

	i = -1;
	window = &cube->window;
	(window->no) && (free(window->no), window->no = NULL);
	(window->so) && (free(window->so), window->so = NULL);
	(window->we) && (free(window->we), window->we = NULL);
	(window->ea) && (free(window->ea), window->ea = NULL);
	(window->f) && (free(window->f), window->f = NULL);
	(window->c) && (free(window->c), window->c = NULL);
	(tmp) && (free(tmp), tmp = NULL);
	(rgb) && (free(rgb), rgb = NULL);
	(cube->pars.fd) && (close(cube->pars.fd), cube->pars.fd = 0);
	ft_error(msg);
}
