/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libattopng3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklarsfe <nklarsfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:01:45 by nklarsfe          #+#    #+#             */
/*   Updated: 2019/11/02 22:48:09 by nklarsfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		libattopng_out_raw_uint16(t_libattopng *png, uint16_t val)
{
	*(uint16_t *)(png->out + png->out_pos) = val;
	png->out_pos += 2;
}

void		libattopng_out_raw_uint8(t_libattopng *png, uint8_t val)
{
	*(uint8_t *)(png->out + png->out_pos) = val;
	png->out_pos++;
}

void		libattopng_new_chunk(t_libattopng *png, const char *name,
										size_t len)
{
	png->crc = 0xffffffff;
	libattopng_out_raw_uint(png, libattopng_swap32((uint32_t)len));
	png->crc = libattopng_crc((const unsigned char *)name, 4, png->crc);
	libattopng_out_raw_write(png, name, 4);
}

void		libattopng_end_chunk(t_libattopng *png)
{
	libattopng_out_raw_uint(png, libattopng_swap32(~png->crc));
}

void		libattopng_out_uint32(t_libattopng *png, uint32_t val)
{
	png->crc = libattopng_crc((const unsigned char *)&val, 4, png->crc);
	libattopng_out_raw_uint(png, val);
}
