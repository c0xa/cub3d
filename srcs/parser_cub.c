/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/11 17:57:41 by tblink           ###   ########.fr       */
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

static char *del_tab_and_sep(char **buf)
{	
	int i;
	char *v;
	char *line;

	line  = *buf;
	i = 0;
	while (line[i] == ' ' || line[i]  == '\t' || line[i]  == '\n')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
		v = ft_strdup(line);
	else
		v = ft_strdup(&line[i]);
	free(*buf);
	return (v);
}

int		parse_parameter(int fd, t_params *params, int flag, int i)
{
	char	*line;
	char 	**buf;

	if ((get_next_line(fd, &line)) <= 0)
		return (-1);
	if (ft_strlen(line) == 0)
		return (0);
	line = del_tab_and_sep(&line);
	if (!(buf = ft_split(line, ' ')))
	{
		free(line);
		return (-1);
	}
	if (buf[0] && ((buf[0][0] >= '0' && buf[0][0] <= '9') || buf[0][0] == ' '))
		return (convert_map(fd, &line, params));
	else
	{
		flag = check_map(buf, params);
		free(line);
	}
	while (buf[i])
		free(buf[i++]);
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
		perror("Error\nFile is not available");
		return (-1);
	}
	flag = parse_parameter(fd, params, 1, 0);
	while (flag == 0)
		flag = parse_parameter(fd, params, 1, 0);
	if (flag == -1 || (!(params->map)))
	{
		perror("Error\nMap is not valid");
		return (-1);
	}
	if ((close(fd)) == -1)
	{
		perror("Error\nFile is not available ");
		return (-1);
	}
	return (1);
}