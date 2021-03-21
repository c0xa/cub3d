/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_spites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/21 20:34:14 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int count_distanse(t_sprite *buf1, t_sprite *buf2, t_tab *tab)
{
	double distance1;
	double distance2;

	distance1 = fabs(tab->rayc->pos_x - buf1->x) + fabs(tab->rayc->pos_y - buf1->y);
	distance2 = fabs(tab->rayc->pos_x - buf2->x) + fabs(tab->rayc->pos_y - buf2->y);
	return (distance1 > distance2);
}

void	sort_sprite(int n, t_tab *tab)
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