/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/26 17:22:54 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_cell(char ceil)
{
	return (ceil != '1' && ceil != ' ');
}

static int	edge_check(t_params *params, int i, int j)
{
	if ((i == 0 || !((params->map)[i + 1]))
			&& check_cell((params->map)[i][j]))
		return (0);
	if (((j == 0 || !((params->map)[i][j + 1]))
			&& check_cell((params->map)[i][j])))
		return (0);
	return (1);
}

static int	near_check(t_params *params, int i, int j)
{
	if ((params->map)[i][j] == ' ' && (params->map)[i][j + 1]
			&& check_cell((params->map)[i][j]))
		return (0);
	if ((params->map)[i][j] == ' ' && (params->map)[i + 1]
			&& (ft_strlen((params->map)[i + 1]) > (unsigned int)j)
			&& check_cell((params->map)[i + 1][j]))
		return (0);
	if (check_cell((params->map)[i][j]) && (params->map)[i][j + 1]
			&& (params->map)[i][j + 1] == ' ')
		return (0);
	if (check_cell((params->map)[i][j]) && (params->map)[i + 1]
			&& ft_strlen((params->map)[i + 1]) > (unsigned int)j
			&& (params->map)[i + 1][j] == ' ')
		return (0);
	if (check_cell((params->map)[i][j]) && (params->map)[i + 1]
			&& (unsigned int)j >= ft_strlen((params->map)[i + 1]))
		return (0);
	if (check_cell((params->map)[i][j]) && i > 0
			&& (unsigned int)j >= ft_strlen((params->map)[i - 1]))
		return (0);
	return (1);
}

static int	check_error_line(t_params *params, int i, int j)
{
	if ((((params->map)[i][j] < '0' || (params->map)[i][j] > '2')
		&& (params->map)[i][j] != ' '
		&& !(params->map[i][j] == 'S' || params->map[i][j] == 'N'
		|| params->map[i][j] == 'E' || params->map[i][j] == 'W'))
		|| (!edge_check(params, i, j)) || !near_check(params, i, j))
		return (0);
	return (1);
}

int			check_error_map(t_params *params, int count_position, int i, int j)
{
	while (params->map[i])
	{
		if (ft_strlen(params->map[i]) == 0)
			return (-1);
		while (params->map[i][j])
		{
			if (params->map[i][j] == 'S' || params->map[i][j] == 'N'
			|| params->map[i][j] == 'E' || params->map[i][j] == 'W')
				count_position++;
			if (!check_error_line(params, i, j) || count_position > 1)
				return (-1);
			j++;
		}
		i++;
		j = 0;
	}
	return (count_position);
}
