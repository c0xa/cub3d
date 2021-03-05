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

int check_params(char *name_map, char *save_flag, t_params *params)
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

int game_start(t_tab *tab, char *map)
{		
	//int				ret;
	t_button		button;
	t_raycasting	rayc;
	t_img			frame_buf;

	if (parse_file(map, tab->params) != 0)
		return (0);
	tab->rayc = &rayc;
	//init_keys(&button);
	tab->button = &button;
	tab->frame_buf = &frame_buf;
	//init_mlx(tab);
	return (0);
}

int	main(int argc, char **argv)
{
	t_tab		tab;
	t_params	params;
	int			t;

	t = 0;
	init_params(&params);
	//errors_arr();
	tab.params = &params;
	if (argc == 3 && check_params(argv[1], argv[2], tab.params))
		t = 1;
	else if (argc == 2 && check_params(argv[1], 0, tab.params))
		t = 1;
	if (t)
		game_start(&tab, argv[1]);
	//print_error(1);
	return (0);
}