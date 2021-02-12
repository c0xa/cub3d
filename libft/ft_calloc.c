/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:32:25 by tblink            #+#    #+#             */
/*   Updated: 2020/11/01 17:23:39 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_calloc(size_t count, size_t size)
{
	void			*buf;
	unsigned char	*p;
	size_t			i;

	i = 0;
	size = size * count;
	buf = malloc(size);
	if (!buf)
		return (0);
	p = buf;
	while (size-- > 0)
	{
		*(p++) = 0;
	}
	return (buf);
}
