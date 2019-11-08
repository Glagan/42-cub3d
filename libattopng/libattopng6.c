/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libattopng6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklarsfe <nklarsfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:01:45 by nklarsfe          #+#    #+#             */
/*   Updated: 2019/11/02 23:41:46 by nklarsfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		libattopng_new_sub1(t_libattopng_type type,
					t_libattopng *png)
{
	if (type == PNG_PALETTE)
	{
		png->palette = (uint32_t *)calloc(256, sizeof(uint32_t));
		if (!png->palette)
		{
			free(png);
			return (EXIT_FAILURE);
		}
		png->bpp = 1;
	}
	else if (type == PNG_GRAYSCALE)
		png->bpp = 1;
	else if (type == PNG_GRAYSCALE_ALPHA)
	{
		png->capacity *= 2;
		png->bpp = 2;
	}
	else if (type == PNG_RGB)
	{
		png->capacity *= 4;
		png->bpp = 3;
	}
	return (EXIT_SUCCESS);
}

int		libattopng_new_sub2(t_libattopng_type type,
					t_libattopng *png)
{
	if (type == PNG_RGBA)
	{
		png->capacity *= 4;
		png->bpp = 4;
	}
	png->data = (char *)calloc(png->capacity, 1);
	if (!png->data)
	{
		free(png->palette);
		free(png);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
