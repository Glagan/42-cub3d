/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libattopng7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklarsfe <nklarsfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:01:45 by nklarsfe          #+#    #+#             */
/*   Updated: 2019/11/02 23:44:38 by nklarsfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			libattopng_get_data_sub1(t_libattopng *png, size_t *len)
{
	if (!png)
		return (EXIT_FAILURE);
	if (png->out)
		free(png->out);
	png->out_capacity = png->capacity + 4096 * 8;
	png->out = (char *)calloc(png->out_capacity, 1);
	png->out_pos = 0;
	if (!png->out)
		return (EXIT_FAILURE);
	libattopng_out_raw_write(png, "\211PNG\r\n\032\n", 8);
	libattopng_new_chunk(png, "IHDR", 13);
	libattopng_out_uint32(png, libattopng_swap32((uint32_t)(png->width)));
	libattopng_out_uint32(png, libattopng_swap32((uint32_t)(png->height)));
	libattopng_out_uint8(png, 8);
	libattopng_out_uint8(png, (uint8_t)png->type);
	libattopng_out_uint8(png, 0);
	libattopng_out_uint8(png, 0);
	libattopng_out_uint8(png, 0);
	libattopng_end_chunk(png);
	(void)len;
	return (EXIT_SUCCESS);
}

void		libattopng_get_data_sub2(t_libattopng *png, size_t *ps,
								char *entry, size_t *pindex)
{
	*ps = png->palette_length;
	if (*ps < 16)
		*ps = 16;
	libattopng_new_chunk(png, "PLTE", 3 * (*ps));
	*pindex = 0;
	while (*pindex < *ps)
	{
		entry[0] = (char)(png->palette[*pindex] & 255);
		entry[1] = (char)((png->palette[*pindex] >> 8) & 255);
		entry[2] = (char)((png->palette[*pindex] >> 16) & 255);
		libattopng_out_write(png, entry, 3);
		(*pindex)++;
	}
	libattopng_end_chunk(png);
	libattopng_new_chunk(png, "tRNS", *ps);
	*pindex = 0;
	while (*pindex < *ps)
	{
		entry[0] = (char)((png->palette[*pindex] >> 24) & 255);
		libattopng_out_write(png, entry, 1);
		(*pindex)++;
	}
	libattopng_end_chunk(png);
}

void		libattopng_get_data_sub3(t_libattopng *png, t_libstuff *pa,
				size_t *pindex)
{
	pa->bpl = 1 + png->bpp * png->width;
	pa->raw_size = png->height * pa->bpl;
	pa->size = 2 + png->height * (5 + pa->bpl) + 4;
	libattopng_new_chunk(png, "IDAT", pa->size);
	libattopng_out_write(png, "\170\332", 2);
	pa->pixel = (unsigned char *)png->data;
	png->s1 = 1;
	png->s2 = 0;
	*pindex = 0;
	if (png->type == PNG_RGB)
		pa->corr = 1;
	else
		pa->corr = 0;
	pa->pos = 0;
}

void		libattopng_get_data_sub4(t_libattopng *png, t_libstuff *pa,
				size_t *pindex)
{
	while (pa->pos < png->width * png->height)
	{
		if (*pindex == 0)
		{
			libattopng_pixel_header(png, pa->raw_size, pa->bpl);
			libattopng_out_write_adler(png, 0);
			pa->raw_size--;
		}
		pa->p = 0;
		while (pa->p < png->bpp)
		{
			libattopng_out_write_adler(png, *pa->pixel);
			pa->pixel++;
			pa->p++;
		}
		pa->pixel += pa->corr;
		pa->raw_size -= png->bpp;
		*pindex = (*pindex + 1) % png->width;
		pa->pos++;
	}
}
