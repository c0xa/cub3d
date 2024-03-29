/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/26 20:11:15 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_strchr_strlen(char *str, int flag)
{
	int n;

	n = 0;
	if (flag)
	{
		while (*str)
		{
			if (*str == '\n')
				return (1);
			str++;
		}
		if (*str == '\n')
			return (1);
		return (0);
	}
	if (!str)
		return (0);
	while (str[n])
		n++;
	return (n);
}

static int	freestr(char **dest, char *src)
{
	char	*tmp;

	tmp = *dest;
	*dest = src;
	free(tmp);
	return (1);
}

static char	*fstrjoin(char *s1, char *s2, int len2)
{
	size_t		len1;
	char		*buf;
	int			i;

	i = 0;
	if (len2 < 0)
		len2 = 0;
	len1 = ft_strchr_strlen(s1, 0);
	if (!(buf = (char*)malloc((len1 + len2 + 1) * sizeof(char))))
		return (NULL);
	while (len1--)
	{
		buf[i] = s1[i];
		i++;
	}
	while (len2--)
	{
		buf[i] = *s2++;
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

static char	*stream(char **line, char *buf)
{
	char		*s;
	int			len;
	int			i;

	i = 0;
	len = 0;
	while (buf[len] != '\n' && buf[len])
	{
		len++;
	}
	freestr(line, fstrjoin(*line, buf, len));
	if (!(s = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (NULL);
	if (buf[len] == '\n' && buf[len])
		len++;
	while (buf[len])
	{
		s[i++] = buf[len++];
	}
	s[i] = '\0';
	return (s);
}

int			writefile(int fd, char **line, char **bufs)
{
	int			l;
	int			k;

	if (ft_strchr_strlen(*bufs, 0))
	{
		l = ft_strchr_strlen(*bufs, 1);
		freestr(bufs, stream(line, *bufs));
		if (l)
			return (1);
	}
	while ((k = read(fd, *bufs, BUFFER_SIZE)))
	{
		if (k == -1)
			return (k);
		(*bufs)[k] = '\0';
		if ((ft_strchr_strlen(*bufs, 1)) && freestr(bufs, stream(line, *bufs)))
			return (1);
		else
			freestr(line, fstrjoin(*line, *bufs, k));
	}
	freestr(line, fstrjoin(*line, *bufs, k));
	return (0);
}
