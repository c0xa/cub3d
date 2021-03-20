/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/20 21:18:39 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_address(t_tab *tab)
{
	tab->e_tex->addr = mlx_get_data_addr(tab->e_tex->img, &(tab->e_tex->bpp),
			&(tab->e_tex->line_len), &(tab->e_tex->endian));
	tab->sprite->addr = mlx_get_data_addr(tab->sprite->img, &(tab->sprite->bpp),
	 		&(tab->sprite->line_len), &(tab->sprite->endian));
	tab->n_tex->addr = mlx_get_data_addr(tab->n_tex->img, &(tab->n_tex->bpp),
			&(tab->n_tex->line_len), &(tab->n_tex->endian));
	tab->w_tex->addr = mlx_get_data_addr(tab->w_tex->img, &(tab->w_tex->bpp),
			&(tab->w_tex->line_len), &(tab->w_tex->endian));
	tab->s_tex->addr = mlx_get_data_addr(tab->s_tex->img, &(tab->s_tex->bpp),
			&(tab->s_tex->line_len), &(tab->s_tex->endian));
}

static void add_texture_1(t_tab *tab)
{
	if (!(tab->n_tex->img = mlx_xpm_file_to_image(tab->mlx_p, tab->params->north,
					&(tab->n_tex->width), &(tab->n_tex->height))))
	{
		perror("Error\nNot valid texture north");
		exit_game(tab);
	}
	if (!(tab->w_tex->img = mlx_xpm_file_to_image(tab->mlx_p, tab->params->west,
					&(tab->w_tex->width), &(tab->w_tex->height))))
	{
		perror("Error\nNot valid texture west");
		exit_game(tab);
	}
	
	if (!(tab->s_tex->img = mlx_xpm_file_to_image(tab->mlx_p, tab->params->south,
					&(tab->s_tex->width), &(tab->s_tex->height))))
	{
		perror("Error\nNot valid texture south");
		exit_game(tab);
	}
}

static void add_texture_2(t_tab *tab)
{
	if (!(tab->e_tex->img = mlx_xpm_file_to_image(tab->mlx_p, tab->params->east,
					&(tab->e_tex->width), &(tab->e_tex->height))))
	{
		perror("Error\nNot valid texture east");
		exit_game(tab);
	}
	if (!(tab->sprite->img = mlx_xpm_file_to_image(tab->mlx_p, tab->params->sprite,
					&(tab->sprite->width), &(tab->sprite->height))))
	{
		perror("Error\nNot valid texture sprite");
		exit_game(tab);
	}
}

void add_texture(t_tab *tab)
{
	add_texture_1(tab);
	add_texture_2(tab);
	add_address(tab);
	printf("add\n");
}
