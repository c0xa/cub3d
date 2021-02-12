/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:24:59 by tblink            #+#    #+#             */
/*   Updated: 2020/10/30 17:21:26 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	while (len >= 0)
	{
		if (str[len] == (char)ch)
			return ((char*)str + len);
		len--;
	}
	return (0);
}
