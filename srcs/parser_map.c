/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/05 22:36:59 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_map(char **buf, t_params *params)
{
	if (!(ft_strncmp(buf[0], "R", 2)))
		return (set_resolution(buf, params));
	if (!(ft_strncmp(buf[0], "NO", 3)))
		return (set_texture(1, buf, params));
	if (!(ft_strncmp(buf[0], "SO", 3)))
		return (set_texture(2, buf, params));
	if (!(ft_strncmp(buf[0], "WE", 3)))
		return (set_texture(3, buf, params));
	if (!(ft_strncmp(buf[0], "EA", 3)))
		return (set_texture(4, buf, params));
	if (!(ft_strncmp(buf[0], "S", 2)))
		return (set_texture(5, buf, params));
	if (!(ft_strncmp(buf[0], "F", 2)))
		return (set_color(1, buf, params));
	if (!(ft_strncmp(buf[0], "C", 2)))
		return (set_color(2, buf, params));
	return (2);
}

int		parse_parameter(int fd, t_params *params, int flag)
{
	char	*line;
	char 	**buf;

	if ((get_next_line(fd, &line)) <= 0)
		return (-1);
	if (!(buf = ft_split(line, ' ')))
	{
		free(line);
		return (-1);
	}
	if (buf[0] && buf[0][0] >= '0' && buf[0][0] <= '9')
		flag = convert_map(fd, &line, params);
	else
	{
		flag = check_map(buf, params);
		free(line);
	}
	if (!buf)
		return (-1);
	while (*buf)
		free(*buf++);
	free(buf);
	return (flag);
}

int		parse_file(char *map, t_params *params)
{
	int fd;
	int	flag;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		perror("File is not available");
		return (0);
	}
	flag = parse_parameter(fd, params, 1);
	while (flag == 1)
		flag = parse_parameter(fd, params, 1);
	if (flag == -1)
		perror("Map is not valid");
	if ((close(fd)) == -1)
	{
		perror("File is not available ");
		return (-1);
	}
	if (fd == 0 && !(params->map))
	{
		perror("Map is not valid");
		return (-1);
	}
	return (fd);
}