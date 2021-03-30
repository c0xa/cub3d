/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/26 20:14:31 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SPEED_MOVE 0.15
#define CAMERA_MOVE 0.05
#include "cub3d.h"

void	motion_a_d(t_tab *tab, int direction)
{
	double	new_pos_y;
	double	new_pos_x;

	new_pos_y = tab->rayc->pos_y + tab->rayc->dir_x * direction * SPEED_MOVE;
	new_pos_x = tab->rayc->pos_x + tab->rayc->dir_y * -direction * SPEED_MOVE;
	if ((tab->params->map)[(int)new_pos_y][(int)tab->rayc->pos_x] == '0')
		tab->rayc->pos_y = new_pos_y;
	if ((tab->params->map)[(int)tab->rayc->pos_y][(int)new_pos_x] == '0')
		tab->rayc->pos_x = new_pos_x;
}

void	motion_w_s(t_tab *tab, int direction)
{
	double	new_pos_y;
	double	new_pos_x;

	new_pos_y = tab->rayc->pos_y + tab->rayc->dir_y * direction * SPEED_MOVE;
	new_pos_x = tab->rayc->pos_x + tab->rayc->dir_x * direction * SPEED_MOVE;
	if ((tab->params->map)[(int)new_pos_y][(int)tab->rayc->pos_x] == '0')
		tab->rayc->pos_y = new_pos_y;
	if ((tab->params->map)[(int)tab->rayc->pos_y][(int)new_pos_x] == '0')
		tab->rayc->pos_x = new_pos_x;
}

void	motion_left(t_tab *tab)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_dir;
	double	sin_dir;

	old_dir_x = tab->rayc->dir_x;
	cos_dir = cos(-CAMERA_MOVE);
	sin_dir = sin(-CAMERA_MOVE);
	tab->rayc->dir_x = tab->rayc->dir_x * cos_dir
		- tab->rayc->dir_y * sin_dir;
	tab->rayc->dir_y = old_dir_x * sin_dir
		+ tab->rayc->dir_y * cos_dir;
	old_plane_x = tab->rayc->plane_x;
	tab->rayc->plane_x = tab->rayc->plane_x * cos_dir
		- tab->rayc->plane_y * sin_dir;
	tab->rayc->plane_y = old_plane_x * sin_dir
		+ tab->rayc->plane_y * cos_dir;
}

void	motion_right(t_tab *tab)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_dir;
	double	sin_dir;

	old_dir_x = tab->rayc->dir_x;
	cos_dir = cos(CAMERA_MOVE);
	sin_dir = sin(CAMERA_MOVE);
	tab->rayc->dir_x = tab->rayc->dir_x * cos_dir
		- tab->rayc->dir_y * sin_dir;
	tab->rayc->dir_y = old_dir_x * sin_dir
		+ tab->rayc->dir_y * cos_dir;
	old_plane_x = tab->rayc->plane_x;
	tab->rayc->plane_x = tab->rayc->plane_x * cos_dir
		- tab->rayc->plane_y * sin_dir;
	tab->rayc->plane_y = old_plane_x * sin_dir
		+ tab->rayc->plane_y * cos_dir;
}
