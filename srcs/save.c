/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/26 20:21:01 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		bitmap_file_header(unsigned int size, int fd)
{
	unsigned char	buf_bitmap_header[14];
	int				i;

	i = 0;
	while (i != 14)
		buf_bitmap_header[i++] = (unsigned int)0;
	buf_bitmap_header[0] = (unsigned int)'B';
	buf_bitmap_header[1] = (unsigned int)'M';
	buf_bitmap_header[2] = (unsigned int)(size & 255);
	buf_bitmap_header[3] = (unsigned int)(size >> 8 & 255);
	buf_bitmap_header[4] = (unsigned int)(size >> 16 & 255);
	buf_bitmap_header[5] = (unsigned int)(size >> 24);
	buf_bitmap_header[10] = (unsigned int)54;
	write(fd, buf_bitmap_header, 14);
}

static void		dib_header(t_tab *tab, int fd)
{
	int		i;
	char	buf_bit_map_intfo_header[40];

	i = 0;
	while (i != 40)
		buf_bit_map_intfo_header[i++] = 0;
	buf_bit_map_intfo_header[0] = (unsigned int)40;
	buf_bit_map_intfo_header[4] = (unsigned int)(tab->params->width & 255);
	buf_bit_map_intfo_header[5] = (unsigned int)(tab->params->width >> 8 & 255);
	buf_bit_map_intfo_header[6] = (unsigned int)
		(tab->params->width >> 16 & 255);
	buf_bit_map_intfo_header[7] = (unsigned int)(tab->params->width >> 24);
	buf_bit_map_intfo_header[8] = (unsigned int)(tab->params->height & 255);
	buf_bit_map_intfo_header[9] = (unsigned int)
		(tab->params->height >> 8 & 255);
	buf_bit_map_intfo_header[10] = (unsigned int)
		(tab->params->height >> 16 & 255);
	buf_bit_map_intfo_header[11] = (unsigned int)(tab->params->height >> 24);
	buf_bit_map_intfo_header[12] = 1;
	buf_bit_map_intfo_header[14] = (unsigned int)tab->frame_buf->bpp;
	write(fd, buf_bit_map_intfo_header, 40);
}

void			save(t_tab *tab, int x, int y, int bit)
{
	unsigned int	size;
	int				fd;

	if ((fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
	{
		printf("Error\nCannot create image file");
		return ;
	}
	size = 54 + tab->params->width * tab->params->height * 4;
	bitmap_file_header(size, fd);
	dib_header(tab, fd);
	y = tab->params->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < tab->params->width)
		{
			bit = *(int*)(tab->frame_buf->addr + (y * tab->frame_buf->line_len
					+ x * (tab->frame_buf->bpp / 8)));
			write(fd, &bit, 4);
			++x;
		}
		--y;
	}
	close(fd);
}
