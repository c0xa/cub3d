/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:35:32 by tblink            #+#    #+#             */
/*   Updated: 2020/11/09 16:37:41 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		sizen(int digit)
{
	size_t len;

	len = 0;
	if (digit == 0)
		return (1);
	while (digit)
	{
		digit /= 10;
		len++;
	}
	return (len);
}

void				ft_putnbr_fd(int num, int fd)
{
	size_t		len;
	long int	digit;
	char		c;
	int			k;

	if (fd < 0)
		return ;
	k = 1;
	digit = num;
	if (digit < 0)
	{
		digit *= -1;
		write(fd, "-", 1);
	}
	len = sizen(num) - 1;
	while (len--)
		k *= 10;
	len = sizen(num);
	while (len--)
	{
		c = digit / k + 48;
		digit %= k;
		k /= 10;
		write(fd, &c, 1);
	}
}
