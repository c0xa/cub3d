/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/20 21:01:36 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_buf(char **arr1, char **arr2)
{
	char **arr2_p;
	int i;

	i = 0;
	arr2_p = arr2;
	while (arr2[i])
	{
		arr1[i] = arr2[i];
		i++;
	}
	free(arr2_p);
}

static int	convert_map_to_arr(int fd, char **line, t_params *params)
{
	int		y;
	int		ret;
	char	**temp;
	int		i;

	y = 1;
	i = 0;
	ret = get_next_line(fd, line);
	while (ret == 1 || (ret == 0 && **line))
	{
		temp = params->map;
		if (!(params->map = (char**)malloc(sizeof(char*) * (y + 2))))
		{
            while (temp[i])
                free(temp[i++]);
            free(temp);
			return (-1);
		}
		move_buf(params->map, temp);
		(params->map)[y] = *line;
		(params->map)[++y] = 0;
		ret = get_next_line(fd, line);
	}
	free(*line);
	return (0);
}


static int	sum_sprites(char **map, int count, int x, int y)
{
	while (map[x])
	{
		y = 0;
		while (map[x][y])
			if (map[x][y++] == '2')
				count++;
		x++;
	}
	return (count);
}

static int			check_other_params(t_params *params)
{
	if ((params->width != -1) && (params->height != -1)
			&& (params->north != 0) && (params->south != 0)
			&& (params->west != 0) && (params->east != 0)
			&& (params->sprite != 0) && (params->floor != -1)
			&& (params->ceiling != -1))
			return (1);
	else
		return (0);
}

int			convert_map(int fd, char **line, t_params *params)
{
	char	**map;
	int		ret;

	ret = check_other_params(params);
	if (!ret)
		return (-1);
	if (!(map = (char**)malloc(sizeof(char*) * 2)))
		return (-1);
	*map = *line;
	*(map + 1) = 0;
	params->map = map;
	if ((ret = convert_map_to_arr(fd, line, params)) != 0)
		return (-1);
	ret = check_error_map(params, 0, 0, 0);
	params->number_of_sprites = sum_sprites(params->map, 0, 0, 0);
	return (ret);
}