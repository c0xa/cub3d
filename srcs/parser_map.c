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
	if (ft_strncmp(buf[0], 'R', 2))
		return (set_resolution(buf, params));
	if (ft_strncmp(buf[0], 'NO', 3))
		return (1, set_texture(buf, params));
	if (ft_strncmp(buf[0], 'SO', 3))
		return (2, set_texture(buf, params));
	if (ft_strncmp(buf[0], 'WE', 3))
		return (3, set_texture(buf, params));
	if (ft_strncmp(buf[0], 'EA', 3))
		return (4, set_texture(buf, params));
	if (ft_strncmp(buf[0], 'S', 2))
		return (5, set_texture(buf, params));
	if (ft_strncmp(buf[0], 'F', 2))
		return (set_color(1, buf, params));
	if (ft_strncmp(buf[0], 'C', 2))
		return (set_color(2, buf, params));
	return (2);
}

int		parse_map(int fd, t_params *params)
{
	char	*line;
	char 	**buf;
	char	**map;
	int		t;
	int		flag;

	while (t = get_next_line(fd, &line) > 0)
	{
		if (!(buf = ft_split(line, ' ')))
			free(line);
			return (1);
		if ((flag = check_map(buf, params)) == 2)
			break;
		if (flag == 1)
			return (-1);
		free(line);
	}
	if (t == -1)
		return (-1);
	if (map_search(char **))
	map = line;
	while (t = get_next_line(fd, &line) > 0)
	{
		buf = ft_split(line, ' ');
		if (!buf)
			return (1);
	}
	get_next_line(fd, &line);
	printf("%s\n", line);
	return (0);
}

int		parse_file(char *map, t_params *params)
{
	(void) params;
	int fd;
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		perror("File is not available");
		return (0);
	}
	if (parse_map(fd, params) != 0)
	{
		perror("Map is not valid");
		return (0);
	}
	if ((close(fd)) == -1)
		return (-1);
	if (ret == 0 && !(params->map))
		return (19);
	return (ret);
	/*
	int i;
	i = 0;
	void *m = mlx_init();
	void *v = mlx_new_window(m, 1000, 1000, "t");
	//void *image_pointer = mlx_new_image(m, 3, 3);
	//char *img_data =  mlx_get_data_addr(m, 8, 2000, 1);
	while (i++ < 850)
		//mlx_put_image_to_window(m, v, image_pointer, i, i);
		mlx_pixel_put(m, v, i, i, 0x00FF0000);
	mlx_loop(m);
	//void *k = mlx_xpm_to_image(m, p, 1, 1);
	//int     mlx_loop_hook (void *mlx_ptr, int (*f)(), void *param);
	//int     mlx_loop (void *mlx_ptr); */
	return (0);
}