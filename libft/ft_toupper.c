/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:24:25 by tblink            #+#    #+#             */
/*   Updated: 2020/11/01 17:28:50 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_toupper(int c)
{
	if (c > 96 && c < 123)
	{
		return (c - 32);
	}
	return (c);
}
