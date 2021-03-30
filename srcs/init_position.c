/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/26 20:12:19 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		init_tab(t_tab *tab, char dir)
{
	tab->rayc->dir_x = 0;
	tab->rayc->dir_y = 0;
	tab->rayc->plane_x = 0;
	tab->rayc->plane_y = 0;
	if (dir == 'W')
	{
		tab->rayc->dir_x = -1;
		tab->rayc->plane_y = 0.7;
	}
	else if (dir == 'E')
	{
		tab->rayc->dir_x = 1;
		tab->rayc->plane_y = -0.7;
	}
	else if (dir == 'N')
	{
		tab->rayc->dir_y = -1;
		tab->rayc->plane_x = -0.7;
	}
	else if (dir == 'S')
	{
		tab->rayc->dir_y = 1;
		tab->rayc->plane_x = 0.7;
	}
}

void			where_is_playes(t_tab *tab, int i, int j)
{
	t_params *params;

	params = tab->params;
	while (params->map[i])
	{
		while (params->map[i][j])
		{
			if (params->map[i][j] == 'S' || params->map[i][j] == 'N'
			|| params->map[i][j] == 'E' || params->map[i][j] == 'W')
			{
				tab->rayc->pos_x = j + 0.5;
				tab->rayc->pos_y = i + 0.5;
				init_tab(tab, params->map[i][j]);
				params->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
		j = 0;
	}
}
