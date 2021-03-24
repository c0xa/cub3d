/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_spites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/23 16:24:05 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int count_distanse(t_sprite *buf1, t_sprite *buf2, t_tab *tab)
{
	double distance1;
	double distance2;

	distance1 = fabs(tab->rayc->pos_x - buf1->x) + fabs(tab->rayc->pos_y - buf1->y);
	distance2 = fabs(tab->rayc->pos_x - buf2->x) + fabs(tab->rayc->pos_y - buf2->y);
	return (distance1 < distance2);
}

static void	sort_sprite(int n, t_tab *tab)
{
	t_sprite s;
	int i;
	int j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (count_distanse(&tab->sprite_arr[j], &tab->sprite_arr[j + 1], tab))
			{
				s = tab->sprite_arr[j + 1];
				tab->sprite_arr[j + 1] = tab->sprite_arr[j];
				tab->sprite_arr[j] = s;							
			}
			j++;
		}
		i++;
	}
}


static void calculate_things_for_sprite(t_tab *tab, int i)
{
	tab->rayc->sprite_x = (tab->sprite_arr[i]).x + 0.5 - tab->rayc->pos_x;
	tab->rayc->sprite_y = (tab->sprite_arr[i]).y + 0.5 - tab->rayc->pos_y;
	tab->rayc->inv_det = 1.0 / (tab->rayc->plane_x * tab->rayc->dir_y
					- tab->rayc->plane_y * tab->rayc->dir_x);
	tab->rayc->transform_x = tab->rayc->inv_det * (tab->rayc->dir_y * tab->rayc->sprite_x
					- tab->rayc->dir_x * tab->rayc->sprite_y);

	tab->rayc->transform_y = tab->rayc->inv_det * (-(tab->rayc->plane_y) * tab->rayc->sprite_x
					+ tab->rayc->plane_x * tab->rayc->sprite_y);
	tab->rayc->sprite_screen_x = (int)(tab->params->width - tab->params->width / 2
					* (1 + tab->rayc->transform_x / tab->rayc->transform_y));
	tab->rayc->sprite_height = fabs((int) tab->params->height / tab->rayc->transform_y);
	tab->rayc->draw_start_y = -(tab->rayc->sprite_height) / 2 + tab->params->height / 2;
	if (tab->rayc->draw_start_y < 0)
		tab->rayc->draw_start_y = 0;
	tab->rayc->draw_end_y = tab->rayc->sprite_height / 2 + tab->params->height / 2;
	if (tab->rayc->draw_end_y >= tab->params->height)
		tab->rayc->draw_end_y = tab->params->height - 1;
	tab->rayc->sprite_width = fabs((int) tab->params->height / tab->rayc->transform_y);
	tab->rayc->draw_start_x = -(tab->rayc->sprite_width) / 2 + tab->rayc->sprite_screen_x;
	if (tab->rayc->draw_start_x < 0)
		tab->rayc->draw_start_x = 0;
	tab->rayc->draw_end_x = tab->rayc->sprite_width / 2 + tab->rayc->sprite_screen_x;
	if (tab->rayc->draw_end_x >= tab->params->width)
		tab->rayc->draw_end_x = tab->params->width - 1;
}



static void draw_sprite(t_tab *tab, int stripe, double *ZBuffer)
{
	int y;
	int d;
	int color;

	while (++stripe < tab->rayc->draw_end_x)
	{
		tab->rayc->tex_x = (int)(256 * (stripe - (-(tab->rayc->sprite_width) / 2
				+ tab->rayc->sprite_screen_x)) * tab->sprite->width / tab->rayc->sprite_width) / 256;
		if (tab->rayc->transform_y > 0 && stripe > 0 && stripe < tab->params->width
				&& tab->rayc->transform_y < ZBuffer[stripe])
		{
			y = tab->rayc->draw_start_y - 1;
			while (++y < tab->rayc->draw_end_y)
			{
				if ((d = y * 256 - tab->params->height
					* 128 + tab->rayc->sprite_height * 128) < 0)
						d = 0;
				tab->rayc->tex_y = ((d * tab->sprite->height)
						/ tab->rayc->sprite_height) / 256;
				color = ((int*)tab->sprite->addr)
					[tab->rayc->tex_y * tab->sprite->width + tab->rayc->tex_x];
				if (color != 0x980088)
					my_mlx_pixel_put(tab->frame_buf, stripe, y, color);
			}
		}
	}
}

void main_sprite(t_tab *tab, double *ZBuffer)
{
	int i;
	int stripe;

	i = -1;
	sort_sprite(tab->params->number_of_sprites, tab);
	while (++i < tab->params->number_of_sprites)
	{
		calculate_things_for_sprite(tab, i);
		stripe = tab->rayc->draw_start_x - 1;
		draw_sprite(tab, stripe, ZBuffer);
	}
}