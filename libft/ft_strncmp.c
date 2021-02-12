/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:59:12 by tblink            #+#    #+#             */
/*   Updated: 2020/11/01 18:07:06 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *string1, const char *string2, size_t num)
{
	unsigned char *s1;
	unsigned char *s2;

	if (num == 0)
		return (0);
	s1 = (unsigned char *)string1;
	s2 = (unsigned char *)string2;
	num--;
	while (num != 0 && *s1 && *s2 && *s1 == *s2)
	{
		num--;
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
