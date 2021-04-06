/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parameter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/04/02 18:27:49 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ch(const char *string)
{
	unsigned long int	n;

	n = 0;
	while (*string == ' ' || *string == '\t' || *string == '\n'
		|| *string == '\v' || *string == '\f' || *string == '\r')
		string++;
	if (*string == '-' || *string == '+')
	{
		if (*string == '-')
			return (-1);
		string++;
	}
	while ((*string >= '0' && *string <= '9') || n >= 9223372036854775807)
		n = n * 10 + *(string++) - '0';
	if (*string > 0 || n >= 9223372036854775807)
		return (-1);
	return ((int)n);
}

int				set_resolution(char **buf, t_params *params)
{
	int height;
	int width;

	if (!buf[1] || !buf[2] || buf[3])
		return (-1);
	if (params->width != -1 && params->height != -1)
		return (-1);
	width = ch(buf[1]);
	height = ch(buf[2]);
	if (height <= 0 || width <= 0)
		return (-1);
	if (width > 2560)
		width = 2560;
	if (height > 1440)
		height = 1440;
	params->height = height;
	params->width = width;
	return (0);
}

int				set_texture(int flag, char **buf, t_params *params)
{
	if (!buf[1] || buf[2])
		return (-1);
	if (flag == 1 && params->north != 0)
		return (-1);
	else if (flag == 2 && params->south != 0)
		return (-1);
	else if (flag == 3 && params->west != 0)
		return (-1);
	else if (flag == 4 && params->east != 0)
		return (-1);
	else if (flag == 5 && params->sprite != 0)
		return (-1);
	if (flag == 1)
		params->north = ft_strdup(buf[1]);
	else if (flag == 2)
		params->south = ft_strdup(buf[1]);
	else if (flag == 3)
		params->west = ft_strdup(buf[1]);
	else if (flag == 4)
		params->east = ft_strdup(buf[1]);
	else if (flag == 5)
		params->sprite = ft_strdup(buf[1]);
	return (0);
}

static int		convert_rgb_to_int(int r, int g, int b)
{
	int t;

	t = r << 16 | g << 8 | b;
	return (t);
}

int				set_color(int flag, char **buf, t_params *params)
{
	char **rgb;

	if (!buf[1] || buf[2])
		return (-1);
	if (flag == 1 && params->floor != -1)
		return (-1);
	else if (flag == 2 && params->ceiling != -1)
		return (-1);
	if (!(rgb = ft_split(buf[1], ",")))
		return (-1);
	if (ch(rgb[0]) > 255 || ch(rgb[1]) > 255 || ch(rgb[2]) > 255
		|| ch(rgb[0]) < 0 || ch(rgb[1]) < 0 || ch(rgb[2]) < 0
		|| count_sep(buf[1]) == -1)
		return (-1);
	if (flag == 1)
		params->floor = convert_rgb_to_int(ft_atoi(rgb[0]),
			ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else
		params->ceiling = convert_rgb_to_int(ft_atoi(rgb[0]),
			ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	return (0);
}
