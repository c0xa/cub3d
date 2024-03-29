/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/30 21:40:51 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				count_sep(char *str)
{
	int i;
	int sum;

	i = 0;
	sum = 0;
	while (str[i])
	{
		if (str[i] == ',')
			sum++;
		i++;
	}
	if (sum != 2)
		return (-1);
	return (0);
}

int				check_params(char *name_map, char *save_flag, t_params *params)
{
	char	*end_line;
	size_t	len;

	if (save_flag != NULL)
	{
		params->save_flag = 1;
		if (ft_strncmp(save_flag, "--save", 7) != 0)
			return (0);
	}
	if ((len = ft_strlen(name_map)) <= 4)
		return (0);
	end_line = name_map + len;
	while (--end_line > name_map)
		if (*end_line == '.')
		{
			if ((ft_strncmp(end_line, ".cub", 5)) == 0)
				return (1);
			return (0);
		}
	return (0);
}

static void		calculate_map_width_height(t_params *params)
{
	size_t x;
	size_t y;
	size_t y_max;

	x = 0;
	y_max = 0;
	while (params->map[x])
	{
		y = 0;
		while (params->map[x][y])
			y++;
		if (y_max < y)
			y_max = y;
		x++;
	}
	params->height_map = x + 1;
	params->width_map = y_max;
}

static int		game_start(t_tab *tab, char *map)
{
	t_button		button;
	t_raycasting	rayc;
	t_img			frame_buf;
	int				i;

	i = parse_file(map, tab->params);
	if (i != 1)
	{
		clean_tab(tab);
		return (0);
	}
	tab->rayc = &rayc;
	init_button(&button);
	tab->button = &button;
	tab->frame_buf = &frame_buf;
	calculate_map_width_height(tab->params);
	draw_and_inital(tab);
	return (0);
}

int				main(int argc, char **argv)
{
	t_tab		tab;
	t_params	params;
	t_img		frame_buf;
	int			t;

	t = 0;
	init_params(&params);
	tab.params = &params;
	tab.frame_buf = &frame_buf;
	if (argc == 3 && check_params(argv[1], argv[2], tab.params))
		t = 1;
	else if (argc == 2 && check_params(argv[1], 0, tab.params))
		t = 1;
	if (t)
		game_start(&tab, argv[1]);
	else
		perror("Error\nNot valid parameter");
	return (0);
}
