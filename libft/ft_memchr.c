/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:24:01 by tblink            #+#    #+#             */
/*   Updated: 2020/10/30 19:43:22 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char *s;

	s = (unsigned char*)src;
	while (n-- > 0)
	{
		if (*s == (unsigned char)c)
			return ((void*)s);
		s++;
	}
	return (NULL);
}
