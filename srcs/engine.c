/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/18 23:46:25 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void real_position(t_raycasting *rayc)
{
	if (rayc->ray_dir_x < 0)
	{
		rayc->step_x = -1;
		rayc->delta_dist_x = (rayc->pos_x - rayc->map_x) * rayc->delta_dist_x;
	}
	else
	{
		rayc->step_x = 1;
		rayc->delta_dist_x = (rayc->map_x + 1.0 - rayc->pos_x) * rayc->delta_dist_x;
	}
	if (rayc->ray_dir_y < 0)
	{
		rayc->step_y = 1;
		rayc->delta_dist_y = (rayc->pos_y - rayc->map_y) * rayc->delta_dist_y;
	}
	else
	{
		rayc->step_y = -1;
		rayc->delta_dist_y = (rayc->map_y + 1.0 - rayc->pos_y) * rayc->delta_dist_y;
	}
}

void	hit_to_wall(t_raycasting *rayc, char **map)
{
	while (rayc->hit == 0)
	{
		if (rayc->side_dist_x < rayc->side_dist_y)
		{
			rayc->side_dist_x += rayc->delta_dist_x;
			rayc->map_x += rayc->step_x;
			rayc->side = 0;
		}
		else
		{
			rayc->side_dist_y += rayc->delta_dist_y;
			rayc->map_y += rayc->step_y;
			rayc->side = 1;
		}
		if (map[rayc->map_y][rayc->map_x] == '1')
			rayc->hit = 1;
	}
	if (rayc->side == 0)
		rayc->perp_wall_dist = (rayc->map_x - (rayc->pos_x)
				+ (1 - rayc->step_x) / 2) / rayc->ray_dir_x;
	else
		rayc->perp_wall_dist = (rayc->map_y - (rayc->pos_y)
				+ (1 - rayc->step_y) / 2) / rayc->ray_dir_y;
}

void calculate_wall(t_raycasting *rayc, int height)
{
	rayc->line_height = (int) (height / rayc->perp_wall_dist);
	rayc->draw_start = -rayc->line_height / 2 + height / 2;
	if (rayc->draw_start < 0)
		rayc->draw_start = 0;
	rayc->draw_end = rayc->line_height / 2 + height / 2;
	if (rayc-> draw_end >= height)
		rayc->draw_end = height - 1;
	if (rayc->draw_end < 0)
		rayc->draw_end = 0;
	printf("perp_wall_dist = %f\n", rayc->perp_wall_dist);
}

void 	engine_main(t_raycasting *rayc, int x, int width)
{

	rayc->camera_x = 2 * (width - x) / (double)width - 1;
	rayc->ray_dir_x = rayc->dir_x + rayc->plane_x * rayc->camera_x;
	rayc->ray_dir_y = rayc->dir_y + rayc->plane_y * rayc->camera_x;
	rayc->delta_dist_x = fabs(1 / rayc->ray_dir_x);
	rayc->delta_dist_y = fabs(1 / rayc->ray_dir_y);
	rayc->map_x = (int)(rayc->pos_x);
	rayc->map_y = (int)(rayc->pos_y);
	rayc->hit = 0;
	real_position(rayc);
}