/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libattopng2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklarsfe <nklarsfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:01:45 by nklarsfe          #+#    #+#             */
/*   Updated: 2019/11/02 22:51:38 by nklarsfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		libattopng_put_pixel(t_libattopng *png, uint32_t color)
{
	size_t x;
	size_t y;

	if (!png)
		return ;
	x = png->stream_x;
	y = png->stream_y;
	if (png->type == PNG_PALETTE || png->type == PNG_GRAYSCALE)
		png->data[x + y * png->width] = (char)(color & 0xff);
	else if (png->type == PNG_GRAYSCALE_ALPHA)
		((uint16_t *)png->data)[x + y * png->width] =
			(uint16_t)(color & 0xffff);
	else
		((uint32_t *)png->data)[x + y * png->width] = color;
	x++;
	if (x >= png->width)
	{
		x = 0;
		y++;
		if (y >= png->height)
			y = 0;
	}
	png->stream_x = x;
	png->stream_y = y;
}

uint32_t	libattopng_swap32(uint32_t num)
{
	return (((num >> 24) & 0xff) |
			((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) |
			((num << 24) & 0xff000000));
}

uint32_t	libattopng_crc(const unsigned char *data, size_t len,
								uint32_t crc)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		crc = g_libattopng_crc32[(crc ^ data[i]) & 255] ^ (crc >> 8);
		i++;
	}
	return (crc);
}

void		libattopng_out_raw_write(t_libattopng *png,
											const char *data, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		png->out[png->out_pos++] = data[i];
		i++;
	}
}

void		libattopng_out_raw_uint(t_libattopng *png, uint32_t val)
{
	*(uint32_t *)(png->out + png->out_pos) = val;
	png->out_pos += 4;
}
