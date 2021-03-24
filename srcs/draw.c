/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/24 21:04:06 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
		my_mlx_pixel_put(frame_buf, x, y, color);
		y++;
	}
}

static void draw_ceil_floor(t_tab* tab, int x, int y)
{
	double zbuffer[tab->params->width];
	change_position_and_camera(tab);
	while (x < (tab->params->width))
	{
		y = 0;
		engine_main(tab->rayc, x, tab->params->width);
		hit_to_wall(tab->rayc, tab->params->map);
		calculate_wall(tab->rayc, tab->params->height);
		calculate_position_wall(tab, tab->rayc, tab->params->height);
		while (y < tab->rayc->draw_start)
			my_mlx_pixel_put(tab->frame_buf, x, y++, tab->params->ceiling);
		draw_wall(tab, tab->frame_buf, x);
		y = tab->rayc->draw_end + 1;
		while (y < tab->params->height)
			my_mlx_pixel_put(tab->frame_buf, x, y++, tab->params->floor);
		zbuffer[x++] = tab->rayc->perp_wall_dist;
	}
	main_sprite(tab, zbuffer);
	printf("5\n");
	if (tab->params->save_flag)
	{
		save(tab, 0, 0, 0);
		printf("6\n");
		exit_game(tab);
	}
}


static void calculate_size_mini_map(t_tab *tab)
{
	tab->map_size = 20;
	while ((tab->map_size * tab->params->height_map) >= tab->params->height)
		tab->map_size--;
	while ((tab->map_size * tab->params->width_map) >= tab->params->width)
		tab->map_size--;
}

static int draw(t_tab *tab)
{
	printf("10\n");
	draw_ceil_floor(tab, 0, 0);
	printf("####\n");
	if (tab->button->space_for_mini_map)
	{
		for (int i = 0; tab->params->map[i]; i++) 
		{
			for (int j = 0; tab->params->map[i][j]; j++) 
			{
				if (i == (int)tab->rayc->pos_y && j == (int)tab->rayc->pos_x) 
					draw_block(j * tab->map_size, i * tab->map_size, tab, 0);
				else if (tab->params->map[i][j] == '1')
					draw_block(j * tab->map_size, i * tab->map_size, tab, convert_rgb_mlx(147, 97, 133));
				else if (tab->params->map[i][j] == '2') 
					draw_block(j * tab->map_size, i * tab->map_size, tab, convert_rgb_mlx(159, 210, 84));
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
	printf("1\n");
	// if (tab->params->save_flag == 0)
	// {
		tab->win_p = mlx_new_window(tab->mlx_p, tab->params->width, tab->params->height, "cub3d");
		mlx_do_key_autorepeatoff(tab->mlx_p);
		mlx_hook(tab->win_p, 17, 0, exit_game, tab);
		mlx_hook(tab->win_p, 2, 0, check_button_press, tab);
		mlx_hook(tab->win_p, 3, 0, check_button_release, tab);
	//}
	printf("2\n");
	tab->frame_buf->img = mlx_new_image(tab->mlx_p, tab->params->width, tab->params->height);
	tab->frame_buf->addr = mlx_get_data_addr(tab->frame_buf->img,
			&(tab->frame_buf->bpp), &(tab->frame_buf->line_len),
			&(tab->frame_buf->endian));
	printf("3\n");
	calculate_size_mini_map(tab);
	where_is_playes(tab, 0, 0);
	init_textures(tab);
	init_sprite(tab);
	printf("4\n");
	mlx_loop_hook(tab->mlx_p, draw, tab);
	mlx_loop(tab->mlx_p);
}
