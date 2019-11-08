/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libattopng4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:01:45 by nklarsfe          #+#    #+#             */
/*   Updated: 2019/11/08 18:07:54 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		libattopng_out_uint16(t_libattopng *png, uint16_t val)
{
	png->crc = libattopng_crc((const unsigned char *)&val, 2, png->crc);
	libattopng_out_raw_uint16(png, val);
}

void		libattopng_out_uint8(t_libattopng *png, uint8_t val)
{
	png->crc = libattopng_crc((const unsigned char *)&val, 1, png->crc);
	libattopng_out_raw_uint8(png, val);
}

void		libattopng_out_write(t_libattopng *png,
				const char *data, size_t len)
{
	png->crc = libattopng_crc((const unsigned char *)data, len, png->crc);
	libattopng_out_raw_write(png, data, len);
}

void		libattopng_out_write_adler(t_libattopng *png, unsigned char data)
{
	libattopng_out_write(png, (char *)&data, 1);
	png->s1 = (uint16_t)((png->s1 + data) % LIBATTOPNG_ADLER_BASE);
	png->s2 = (uint16_t)((png->s2 + png->s1) % LIBATTOPNG_ADLER_BASE);
}

void		libattopng_pixel_header(t_libattopng *png,
				size_t offset, size_t bpl)
{
	if (offset > bpl)
	{
		libattopng_out_write(png, "\0", 1);
		libattopng_out_uint16(png, (uint16_t)bpl);
		libattopng_out_uint16(png, (uint16_t)~bpl);
	}
	else
	{
		libattopng_out_write(png, "\1", 1);
		libattopng_out_uint16(png, (uint16_t)offset);
		libattopng_out_uint16(png, (uint16_t)~offset);
	}
}
