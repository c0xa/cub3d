/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/02/12 20:18:58 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
void	errors_arr(void)
{
	g_errors[1] = "Error\nInvalid arguments\n";
	g_errors[2] = "Error\nInvalid parameter in description file\n";
	g_errors[3] = "Error\nMap must be the last parameter in description file\n";
	g_errors[4] = "Error\nMap has empty lines\n";
	g_errors[5] = "Error\nToo few resolution parameters\n";
	g_errors[6] = "Error\nToo many resolution parameters\n";
	g_errors[7] = "Error\nNull or negative resolution\n";
	g_errors[8] = "Error\nNo texture parameter\n";
	g_errors[9] = "Error\nToo many texture parameters\n";
	g_errors[10] = "Error\nNo color parameter\n";
	g_errors[11] = "Error\nToo many color parameters\n";
	g_errors[12] = "Error\nInvalid color parameter\n";
	g_errors[13] = "Error\nNegative color\n";
	g_errors[14] = "Error\nMap not surrounded by walls\n";
	g_errors[15] = "Error\nInvalid player position\n";
	g_errors[16] = "Error\nMap has invalid characters\n";
	g_errors[17] = "Error\nColor value more than 255\n";
	g_errors[18] = "Error\nInvalid resolution parameters\n";
	g_errors[19] = "Error\nNo map\n";
	g_errors[20] = "Error\nDouble parameter\n";
	g_errors[21] = "Error\nInvalid texture image\n";
}

void	print_error(int err_code)
{
	if (err_code == -1)
	{
		perror("Error\n");
		return ;
	}
	if (err_code <= 0 || err_code >= 22)
	{
		write(2, "Unknown error happened\n", 23);
		return ;
	}
	write(2, g_errors[err_code], ft_strlen(g_errors[err_code]));
}
*/