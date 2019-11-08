/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libattopng5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklarsfe <nklarsfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:01:45 by nklarsfe          #+#    #+#             */
/*   Updated: 2019/11/02 23:35:20 by nklarsfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			*libattopng_get_data(t_libattopng *png, size_t *len)
{
	size_t			index;
	char			entry[3];
	size_t			s;
	t_libstuff		a;

	if (libattopng_get_data_sub1(png, len) == EXIT_FAILURE)
		return (NULL);
	if (png->type == PNG_PALETTE)
		libattopng_get_data_sub2(png, &s, entry, &index);
	libattopng_get_data_sub3(png, &a, &index);
	libattopng_get_data_sub4(png, &a, &index);
	png->s1 %= LIBATTOPNG_ADLER_BASE;
	png->s2 %= LIBATTOPNG_ADLER_BASE;
	libattopng_out_uint32(png,
		libattopng_swap32((uint32_t)((png->s2 << 16) | png->s1)));
	libattopng_end_chunk(png);
	libattopng_new_chunk(png, "IEND", 0);
	libattopng_end_chunk(png);
	if (len)
		*len = png->out_pos;
	return (png->out);
}

int				libattopng_save(t_libattopng *png, const char *filename)
{
	size_t	len;
	int		f;
	char	*data;

	data = libattopng_get_data(png, &len);
	if (!data)
		return (1);
	f = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (f == -1)
		return (1);
	if (write(f, data, len) != 1)
	{
		close(f);
		return (1);
	}
	close(f);
	return (0);
}

void			libattopng_destroy(t_libattopng *png)
{
	if (!png)
		return ;
	free(png->palette);
	png->palette = NULL;
	free(png->out);
	png->out = NULL;
	free(png->data);
	png->data = NULL;
	free(png);
}
