/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:50:47 by tblink            #+#    #+#             */
/*   Updated: 2021/03/24 18:45:17 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	countc(char const *s, char *str)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (s[i])
	{
		while (ft_strchr(str, s[i]))
			i++;
		if (s[i])
			len++;
		while (!ft_strchr(str, s[i]))
			i++;
	}
	return (len);
}

static void	*ft_clean(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static int	countw(char const *s, char *str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (ft_strchr(str, s[i]))
		i++;
	while (!ft_strchr(str, s[i]))
	{
		i++;
		len++;
	}
	return (len);
}

char		**ft_split(char const *s, char *str)
{
	int		b;
	int		i;
	int		j;
	char	**buf;

	i = 0;
	b = -1;
	if (!s || !(buf = (char**)malloc(sizeof(char*) * (countc(s, str) + 1))))
		return (NULL);
	while (++b < countc(s, str))
	{
		j = 0;
		if (!(buf[b] = (char*)malloc(sizeof(char) * (countw(&s[i], str) + 1))))
		{
			ft_clean(buf, b);
			return (NULL);
		}
		while (ft_strchr(str, s[i]))
			i++;
		while (!ft_strchr(str, s[i]))
			buf[b][j++] = s[i++];
		buf[b][j] = '\0';
	}
	buf[b] = NULL;
	return (buf);
}
