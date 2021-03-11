/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/11 22:11:14 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int exit_game(void *arg) {
	t_tab *tab;

	tab = (t_tab*)arg;
	mlx_destroy_window(tab->mlx_p, tab->win_p);
	//clean
	exit(0);
}

int draw(void* arg) {
	t_tab *tab;
	int i;
	int j;

	i = 0;
	j = 0;
	tab = (t_tab*)arg;
	while (i < tab->params->height/2)
	{
		while (j < tab->params->width)
		{
			mlx_pixel_put(tab->mlx_p, tab->win_p, j, i, tab->params->ceiling);
			j++;
		}
		i++;
		j = 0;
	}
	j = 0;
	while (i < tab->params->height)
	{
		while (j < tab->params->width)
		{
			mlx_pixel_put(tab->mlx_p, tab->win_p, j, i, tab->params->floor);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

void draw_ceil_floor(t_tab *tab)
{
	tab->mlx_p = mlx_init();
	tab->win_p = mlx_new_window(tab->mlx_p, tab->params->width, tab->params->height, "cub3d");

	mlx_hook(tab->win_p, 17, 0, exit_game, tab);
	mlx_loop_hook(tab->mlx_p, draw, tab);
	mlx_loop(tab->mlx_p);
}