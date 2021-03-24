/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/24 18:44:31 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_params(char *name_map, char *save_flag, t_params *params)
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

void	free_object(t_params *params)
{
	int i;

	i = 0;
	if (params->east)
		free(params->east);
	if (params->south)
		free(params->south);
	if (params->west)
		free(params->west);
	if (params->east)
		free(params->east);
	if (params->sprite)
		free(params->sprite);
	if (params->map == NULL)
		return;
	while (params->map[i])
		free(params->map[i++]);
	free(params->map);
}

// static void check(t_params *params)
// {
// 	printf("width %d\n", params->width);
// 	printf("height %d\n", params->height);
// 	printf("floor %d\n", params->floor);
// 	printf("ceiling %d\n", params->ceiling);
// 	printf("number_of_sprites %d\n", params->number_of_sprites);
// 	printf("north %s\n", params->north);
// 	printf("south %s\n", params->south);
// 	printf("west %s\n", params->west);
// 	printf("east %s\n", params->east);
// }

static void	calculate_map_width_height(t_params *params)
{
	int x;
	int y;
	int y_max;

	x = 0;
	y = 0;
	y_max = 0;
	while (params->map[x])
	{
		while (params->map[x][y])
			y++;
		if (y_max < y)
			y_max = y;
		x++;
	}
	params->height_map = x + 1;
	params->width_map = y_max;
}

static	int	game_start(t_tab *tab, char *map)
{
	t_button		button;
	t_raycasting	rayc;
	t_img			frame_buf;
	int i;

	i = parse_file(map, tab->params);
	if (i != 1)
	{
		//check(tab->params);
		printf("finish\n");
		//free_object(tab->params);
		//init_params(tab->params);
		//check(tab->params);
		return (0);
	}
	//check(tab->params);
	tab->rayc = &rayc;
	init_button(&button);
	tab->button = &button;
	tab->frame_buf = &frame_buf;
	calculate_map_width_height(tab->params);
	draw_and_inital(tab);
	return (0);
}

int	main(int argc, char **argv)
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
