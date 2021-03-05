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

int			parse_file(char *name_file, t_params *params)
{
	int fd;
	int ret;

	if ((fd = open(name_file, O_RDONLY)) == -1)
		return (-1);
	ret = parse_line(fd, params);
	while (ret == 1)
		ret = parse_line(fd, params);
	if ((close(fd)) == -1)
		return (-1);
	if (ret == 0 && !(params->map))
		return (19);
	return (ret);
}