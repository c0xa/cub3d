/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:36 by tblink            #+#    #+#             */
/*   Updated: 2021/03/24 21:10:09 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// static void	write_bmp_header(int fd, int bmp_size)
// {
// 	unsigned char	header[14];
// 	int				i;

// 	i = 0;
// 	while (i < 14)
// 		header[i++] = (unsigned char)0;
// 	header[0] = (unsigned char)'B';
// 	header[1] = (unsigned char)'M';
// 	int_to_uchar(&(header[2]), bmp_size);
// 	header[10] = (unsigned char)54;
// 	write(fd, header, 14);
// }

static void bitmap_file_header(unsigned int size, int fd)
{
	unsigned char	buf_bitmap_header[14];
	int i = 0;
	while (i != 14)
		buf_bitmap_header[i++] = (unsigned int)0;
	buf_bitmap_header[0] = (unsigned int)'B';
	buf_bitmap_header[1] = (unsigned int)'M';
	//buf_bitmap_header[2] = (unsigned int)size;
	buf_bitmap_header[2] = (unsigned int)(size & 255);
	buf_bitmap_header[3] = (unsigned int)(size >> 8 & 255);
	buf_bitmap_header[4] = (unsigned int)(size >> 16 & 255);
	buf_bitmap_header[5] = (unsigned int)(size >> 24);
	buf_bitmap_header[10] = (unsigned int)52;

	// i = 0;
	// while (i != 14)
	// 	printf("buf = %c\n", buf_bitmap_header[i++]);
	write(fd, buf_bitmap_header, 14);
}


static void	int_to_uchar(unsigned char *arr, int x)
{
	arr[0] = (unsigned char)(x & 255);
	arr[1] = (unsigned char)(x >> 8 & 255);
	arr[2] = (unsigned char)(x >> 16 & 255);
	arr[3] = (unsigned char)(x >> 24);
}

static void	write_dib_header(int fd, int width, int height, int bpp)
{
	unsigned char	header[40];
	int				i;

	i = 0;
	while (i < 40)
		header[i++] = (unsigned char)0;
	header[0] = (unsigned char)40;
	int_to_uchar(&(header[4]), width);
	int_to_uchar(&(header[8]), height);
	header[12] = (unsigned char)1;
	header[14] = (unsigned char)bpp;
	write(fd, header, 40);
}

// static void	write_pixels(int fd, t_tab *tab)
// {
// 	int				x;
// 	int				y;
// 	int				color;

// 	y = tab->params->height - 1;
// 	while (y >= 0)
// 	{
// 		x = 0;
// 		while (x < tab->params->width)
// 		{
// 			color = *(int*)(tab->frame_buf->addr + (y * tab->frame_buf->line_len
// 					+ x * (tab->frame_buf->bpp / 8)));
// 			write(fd, &color, 4);
// 			x++;
// 		}
// 		y--;
// 	}
// }

// static void dib_header(char *buf_bit_map_intfo_header, t_tab *tab, int fd)
// {
// 	int i;

// 	i = 0;
// 	while (i != 40)
// 		buf_bit_map_intfo_header[i++] = 0;
// 	buf_bit_map_intfo_header[0] = (unsigned int)40;
// 	buf_bit_map_intfo_header[4] = (unsigned int)(tab->params->width & 255);
// 	buf_bit_map_intfo_header[5] = (unsigned int)(tab->params->width >> 8 & 255);
// 	buf_bit_map_intfo_header[6] = (unsigned int)(tab->params->width >> 16 & 255);
// 	buf_bit_map_intfo_header[7] = (unsigned int)(tab->params->width >> 24);
// 	buf_bit_map_intfo_header[8] = (unsigned int)(tab->params->height & 255);
// 	buf_bit_map_intfo_header[9] = (unsigned int)(tab->params->height >> 8 & 255);
// 	buf_bit_map_intfo_header[10] = (unsigned int)(tab->params->height >> 16 & 255);
// 	buf_bit_map_intfo_header[11] = (unsigned int)(tab->params->height >> 24);
// 	// buf_bit_map_intfo_header[4] = (unsigned int)tab->params->width;
// 	// buf_bit_map_intfo_header[8] = (unsigned int)tab->params->height;

// 	buf_bit_map_intfo_header[12] = 1;
// 	buf_bit_map_intfo_header[14] = (unsigned int)tab->frame_buf->bpp; //32
// 	write(fd, buf_bit_map_intfo_header, 40);
// }

void	save(t_tab *tab, int x, int y, int bit)
{
	unsigned int size;

	// char buf_bit_map_intfo_header[40];
	int fd;

	// (void) x;
	// (void) y;
	// (void) bit;
	if ((fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
	{
		printf("Error\nCannot create image file");
		return ;
	}
	size = 54 + tab->params->width * tab->params->height * 4;
	bitmap_file_header(size, fd);
	// dib_header(buf_bit_map_intfo_header, tab, fd);
	//write_bmp_header(fd, size);
	printf("11\n");
	write_dib_header(fd, tab->params->width,
			tab->params->height, tab->frame_buf->bpp);
	printf("12\n");
	//write_pixels(fd, tab);
	printf("13\n");
	//close(fd);

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