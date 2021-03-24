/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assistant_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/23 22:08:27 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *frame_buf, int x, int y, int color)
{
    char    *dst;

    dst = frame_buf->addr + (y * frame_buf->line_len + x * (frame_buf->bpp / 8));
    *(int*)dst = color;
}

int exit_game(void *arg) {
	t_tab *tab;

	tab = (t_tab*)arg;
	mlx_destroy_window(tab->mlx_p, tab->win_p);
	//clean
	exit(0);
}

int draw_block(int x, int y, t_tab *tab, int color)
{
	int i;
	int j;

	i = y;
	while (i < y + tab->map_size)
	{
		j = x;
		while (j < x + tab->map_size)
		{
			my_mlx_pixel_put(tab->frame_buf, j, i, color);
			j++;
		}
		i++;
	}
	return (0);
}

int convert_rgb_mlx(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
