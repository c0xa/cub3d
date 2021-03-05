/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/05 18:02:41 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_params(t_params *params)
{
	params->save_flag = 0;
	params->width = -1;
	params->height = -1;
	params->north = 0;
	params->south = 0;
	params->west = 0;
	params->east = 0;
	params->sprite = 0;
	params->floor = -1;
	params->ceiling = -1;
	params->map = 0;
	params->number_of_sprites = 0;
}

void init_sprite (t_sprite *sprite)
{
    sprite->x = 0;
    sprite->y = 0;
}

void	init_button(t_button *button)
{
	button->w = 0;
	button->a = 0;
	button->s = 0;
	button->d = 0;
	button->left = 0;
	button->right = 0;
}