/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:13:13 by tblink            #+#    #+#             */
/*   Updated: 2020/11/09 16:21:16 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s, char const *set)
{
	char			*buf;
	char			*start;
	char			*end;
	int				i;

	i = 0;
	if (!s)
		return (NULL);
	while (*s && ft_strchr(set, *s))
		s++;
	start = (char *)s;
	while (*s)
		s++;
	s--;
	while (s > start && ft_strchr(set, *s))
		s--;
	end = (char *)s;
	if (!(buf = (char*)malloc((end - start + 2) * sizeof(char))))
		return (NULL);
	while (start <= end)
		buf[i++] = *start++;
	buf[i] = '\0';
	return (buf);
}
