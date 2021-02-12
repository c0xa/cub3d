/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:22:11 by tblink            #+#    #+#             */
/*   Updated: 2020/11/09 16:20:44 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	i;
	size_t	len;

	j = 0;
	i = 0;
	len = 0;
	j = ft_strlen(dst);
	len = ft_strlen(src);
	if (size < j)
		return (size + len);
	if (size <= j)
		len += size;
	else
		len += j;
	while (src[i] && j + 1 < size)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (len);
}
