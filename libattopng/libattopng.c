/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libattopng.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:01:45 by nklarsfe          #+#    #+#             */
/*   Updated: 2019/11/08 18:21:08 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** libattopng
** A minimal C library to write uncompressed PNG files.
**
** libattopng is a minimal C library to create uncompressed PNG images.
** It is cross-platform compatible, has no dependencies and
** a very small footprint.
** The library supports palette, grayscale as well as raw RGB images,
** all with and without transparency.
**
** author Michael Schwarz
** date 29 Jan 2017
*/

#include "cub3d.h"

t_libattopng	*libattopng_new(size_t width,
					size_t height, t_libattopng_type type)
{
	t_libattopng *png;

	if (SIZE_MAX / 4 / width < height)
		return (NULL);
	png = (t_libattopng *)calloc(sizeof(t_libattopng), 1);
	png->width = width;
	png->height = height;
	png->capacity = width * height;
	png->palette_length = 0;
	png->palette = NULL;
	png->out = NULL;
	png->out_capacity = 0;
	png->out_pos = 0;
	png->type = type;
	png->stream_x = 0;
	png->stream_y = 0;
	if (libattopng_new_sub1(type, png))
		return (NULL);
	if (libattopng_new_sub2(type, png))
		return (NULL);
	return (png);
}

int				libattopng_set_palette(t_libattopng *png,
					uint32_t *palette, size_t length)
{
	if (length > 256)
		return (1);
	ft_memmove(png->palette, palette, length * sizeof(uint32_t));
	png->palette_length = length;
	return (0);
}

void			libattopng_set_pixel(t_libattopng *png,
					size_t x, size_t y, uint32_t color)
{
	if (!png || x >= png->width || y >= png->height)
		return ;
	if (png->type == PNG_PALETTE || png->type == PNG_GRAYSCALE)
		png->data[x + y * png->width] = (char)(color & 0xff);
	else if (png->type == PNG_GRAYSCALE_ALPHA)
		((uint16_t *)png->data)[x + y * png->width] =
			(uint16_t)(color & 0xffff);
	else
		((uint32_t *)png->data)[x + y * png->width] = color;
}

uint32_t		libattopng_get_pixel(t_libattopng *png, size_t x, size_t y)
{
	uint32_t pixel;

	pixel = 0;
	if (!png || x >= png->width || y >= png->height)
		return (pixel);
	if (png->type == PNG_PALETTE || png->type == PNG_GRAYSCALE)
		pixel = (uint32_t)(png->data[x + y * png->width] & 0xff);
	else if (png->type == PNG_GRAYSCALE_ALPHA)
		pixel =
			(uint32_t)(((uint16_t *)png->data)[x + y * png->width]
				& 0xffff);
	else
		pixel = ((uint32_t *)png->data)[x + y * png->width];
	return (pixel);
}

void			libattopng_start_stream(t_libattopng *png, size_t x, size_t y)
{
	if (!png || x >= png->width || y >= png->height)
		return ;
	png->stream_x = x;
	png->stream_y = y;
}
