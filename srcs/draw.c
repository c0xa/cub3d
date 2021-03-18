/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/18 23:46:32 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CELL 20

#include "cub3d.h"

void            my_mlx_pixel_put(t_img *frame_buf, int x, int y, int color)
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

int convert_rgb_mlx(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int draw_block(int x, int y, t_tab *tab, int color)
{
	int i;
	int j;

	i = y;
	while (i < y + CELL)
	{
		j = x;
		while (j < x + CELL)
		{
			my_mlx_pixel_put(tab->frame_buf, j, i, color);
			j++;
		}
		i++;
	}
	return (0);
}

int draw_ceil_floor(t_tab* tab)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < (tab->params->width))
	{
		engine_main(tab->rayc, x, tab->params->width);
		hit_to_wall(tab->rayc, tab->params->map);
		y = 0;
		calculate_wall(tab->rayc, tab->params->height);
		while (y < tab->rayc->draw_start)
		{
			my_mlx_pixel_put(tab->frame_buf, x, y, tab->params->ceiling);
			y++;
		}
		printf("draw_start = %d\n", tab->rayc->draw_start);
		printf("draw_end = %d\n\n", tab->rayc->draw_end);
		while (y <= tab->rayc->draw_end)
			my_mlx_pixel_put(tab->frame_buf, x, y++, convert_rgb_mlx(0, 0, 255));
		while (y < tab->params->height)
		{
			my_mlx_pixel_put(tab->frame_buf, x, y, tab->params->floor);
			y++;
		}
		x++;
	}
	return (0);
}

int draw(t_tab *tab)
{
	if (tab->button->w == 1)
		tab->rayc->pos_y -= 1;
	if (tab->button->a == 1)
		tab->rayc->pos_x -= 1;
	if (tab->button->s == 1)
		tab->rayc->pos_y += 1;
	if (tab->button->d == 1)
		tab->rayc->pos_x += 1;	
	draw_ceil_floor(tab);
	for (int i = 0; tab->params->map[i]; i++) {
		for (int j = 0; tab->params->map[i][j]; j++) {
			if (i == (int)tab->rayc->pos_y && j == (int)tab->rayc->pos_x) {
				draw_block(j * CELL, i * CELL, tab, 0);
			}
			else if (tab->params->map[i][j] == '1') {
				draw_block(j * CELL, i * CELL, tab, convert_rgb_mlx(0, 0, 255));
			}
		}
	}
	mlx_clear_window(tab->mlx_p, tab->win_p);
	mlx_put_image_to_window(tab->mlx_p, tab->win_p, tab->frame_buf->img, 0, 0);
	return (0);
}



void draw_and_inital(t_tab *tab)
{
	tab->mlx_p = mlx_init();
	tab->win_p = mlx_new_window(tab->mlx_p, tab->params->width, tab->params->height, "cub3d");
	tab->frame_buf->img = mlx_new_image(tab->mlx_p, tab->params->width, tab->params->height);
	tab->frame_buf->addr = mlx_get_data_addr(tab->frame_buf->img,
			&(tab->frame_buf->bpp), &(tab->frame_buf->line_len),
			&(tab->frame_buf->endian));
	where_is_playes(tab, 0, 0);
	mlx_do_key_autorepeatoff(tab->mlx_p);
	mlx_hook(tab->win_p, 17, 0, exit_game, tab);
	mlx_hook(tab->win_p, 2, 0, check_button_press, tab);
	mlx_hook(tab->win_p, 3, 0, check_button_release, tab);
	mlx_loop_hook(tab->mlx_p, draw, tab);
	mlx_loop(tab->mlx_p);
}
