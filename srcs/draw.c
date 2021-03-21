/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/21 20:19:15 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void draw_wall(t_tab* tab, t_img *frame_buf, int x)
{
	int	color;
	int y;

	y = tab->rayc->draw_start;
	while (y <= tab->rayc->draw_end)
	{
		tab->rayc->tex_y = (int)(tab->rayc->tex_pos) & (tab->rayc->tex->height - 1);
		tab->rayc->tex_pos += tab->rayc->tex_step;
		color = ((int*)tab->rayc->tex->addr)
			[tab->rayc->tex_y * tab->rayc->tex->width + tab->rayc->tex_x];
		// if (tab->rayc->side == 1)
		// 	color = color;
		my_mlx_pixel_put(frame_buf, x, y, color);
		y++;
	}
}

int draw_ceil_floor(t_tab* tab, int x, int y)
{
	change_position_and_camera(tab);
	while (x < (tab->params->width))
	{
		engine_main(tab->rayc, x, tab->params->width);
		hit_to_wall(tab->rayc, tab->params->map);
		y = 0;
		calculate_wall(tab->rayc, tab->params->height);
		calculate_position_wall(tab, tab->rayc, tab->params->height);
		while (y < tab->rayc->draw_start)
		{
			my_mlx_pixel_put(tab->frame_buf, x, y, tab->params->ceiling);
			y++;
		}
		draw_wall(tab, tab->frame_buf, x);
		y = tab->rayc->draw_end + 1;
		while (y < tab->params->height)
		{
			my_mlx_pixel_put(tab->frame_buf, x, y, tab->params->floor);
			y++;
		}
		x++;
		sort_sprite(tab->params->number_of_sprites, tab);
	}
	int i;
		
		i = 0;
		printf("\n================================\n");
		while (i < tab->params->number_of_sprites)
		{
			printf("x = %d\n", (tab->sprite_arr[i]).x);	
			printf("y = %d\n", (tab->sprite_arr[i]).y);					
			i++;
		}
		printf("\n================================\n");
	return (0);
}

int draw(t_tab *tab)
{
	draw_ceil_floor(tab, 0, 0);
	for (int i = 0; tab->params->map[i]; i++) {
		for (int j = 0; tab->params->map[i][j]; j++) {
			if (i == (int)tab->rayc->pos_y && j == (int)tab->rayc->pos_x) {
				draw_block(j * tab->map_size, i * tab->map_size, tab, 0);
			}
			else if (tab->params->map[i][j] == '1') {
				draw_block(j * tab->map_size, i * tab->map_size, tab, convert_rgb_mlx(147, 97, 133));
			}
		}
	}
	mlx_clear_window(tab->mlx_p, tab->win_p);
	mlx_put_image_to_window(tab->mlx_p, tab->win_p, tab->frame_buf->img, 0, 0);
	return (0);
}



void draw_and_inital(t_tab *tab)
{
	t_sprite sprite_array[tab->params->number_of_sprites];
	tab->sprite_arr = &sprite_array[0];
	tab->mlx_p = mlx_init();
	tab->win_p = mlx_new_window(tab->mlx_p, tab->params->width, tab->params->height, "cub3d");
	tab->frame_buf->img = mlx_new_image(tab->mlx_p, tab->params->width, tab->params->height);
	tab->frame_buf->addr = mlx_get_data_addr(tab->frame_buf->img,
			&(tab->frame_buf->bpp), &(tab->frame_buf->line_len),
			&(tab->frame_buf->endian));
	tab->map_size = (tab->params->height * tab->params->width) / 100000;
	printf("map = %d\n", tab->map_size);
	printf("map = %d\n", tab->params->width_map * tab->params->height_map);
	printf("map = %d\n", tab->params->height * tab->params->width);
	printf("map = %d\n", (tab->params->height * tab->params->width) / (tab->params->width_map * tab->params->height_map));
	if ((tab->params->height * tab->params->width) / (tab->params->width_map * tab->params->height_map) > 1100)
	{
		printf("F\n");
		tab->map_size = 10;
	}
	while ((tab->map_size * tab->params->height_map) >= tab->params->height)
		tab->map_size--;
	while ((tab->map_size * tab->params->width_map) >= tab->params->width)
		tab->map_size--;
	where_is_playes(tab, 0, 0);
	mlx_do_key_autorepeatoff(tab->mlx_p);
	mlx_hook(tab->win_p, 17, 0, exit_game, tab);
	mlx_hook(tab->win_p, 2, 0, check_button_press, tab);
	mlx_hook(tab->win_p, 3, 0, check_button_release, tab);
	init_textures(tab);
	init_sprite(tab);
	mlx_loop_hook(tab->mlx_p, draw, tab);
	mlx_loop(tab->mlx_p);
}
