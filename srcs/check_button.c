/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_button.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/14 18:51:11 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_button_press(int but, t_tab *tab)
{
	if (but == 53)
	{
		exit_game(tab);
		return (0);
	}
	if (but == 13)
		(tab->button)->w = 1;
	else if (but == 0)
		(tab->button)->a = 1;
	else if (but == 1)
		(tab->button)->s = 1;
	else if (but == 2)
		(tab->button)->d = 1;
	else if (but == 123)
		(tab->button)->left = 1;
	else if (but == 124)
		(tab->button)->right = 1;
	return (0);
}

int check_button_release(int but, t_tab *tab)
{
	if (but == 13)
		(tab->button)->w = 0;
	else if (but == 0)
		(tab->button)->a = 0;
	else if (but == 1)
		(tab->button)->s = 0;
	else if (but == 2)
		(tab->button)->d = 0;
	else if (but == 123)
		(tab->button)->left = 0;
	else if (but == 124)
		(tab->button)->right = 0;
	return (0);
}