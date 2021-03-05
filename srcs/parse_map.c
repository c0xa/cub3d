/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/02/12 20:18:58 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	move_arr(char **arr1, char **arr2)
{
	char **arr2_p;

	arr2_p = arr2;
	while (*arr2)
		*arr1++ = *arr2++;
	free(arr2_p);
}

static int	convert_map_to_arr(int fd, char **line, t_params *params)
{
	int		y;
	int		ret;
	char	**temp;

	y = 1;
	ret = get_next_line(fd, line);
	while (ret == 1 || (ret == 0 && **line))
	{
		temp = params->map;
		if (!(params->map = (char**)malloc(sizeof(char*) * (y + 2))))
		{
			free_string_arr(temp);
			return (-1);
		}
		move_arr(params->map, temp);
		(params->map)[y] = *line;
		(params->map)[++y] = 0;
		ret = get_next_line(fd, line);
	}
	free(*line);
	return (0);
}

int			other_params_set(t_params *params)
{
	return ((params->width != -1) && (params->height != -1)
			&& (params->north != 0) && (params->south != 0)
			&& (params->west != 0) && (params->east != 0)
			&& (params->sprite != 0) && (params->floor != -1)
			&& (params->ceiling != -1));
}

int			count_sprites(char **map)
{
	int count;
	int y;
	int x;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int			parse_map(int fd, char **line, t_params *params)
{
	char	**map;
	int		ret;

	if (!(other_params_set(params)))
		return (3);
	if (!(map = (char**)malloc(sizeof(char*) * 2)))
		return (-1);
	*map = *line;
	*(map + 1) = 0;
	params->map = map;
	if ((ret = convert_map_to_arr(fd, line, params)) != 0)
		return (ret);
	//ret = check_map(params);
	params->number_of_sprites = count_sprites(params->map);
	return (ret);
}