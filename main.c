/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:45:06 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 11:51:43 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mlx/mlx.h"
#include "config/config.h"

int
	main(int argc, char **argv)
{
	int			i;
	int			j;
	t_config	*config;

	if (argc != 2) // todo: look for -save
		return (printf("Error:\nMissing configuration file.\n")); // todo: print "Error"
	if ((config = parse_config(argv[1])))
	{
		printf("{\n\twidth:%d," \
			"\n\theight:%d," \
			"\n\tno_texture:\"%s\"," \
			"\n\tso_texture:\"%s\"," \
			"\n\twe_texture:\"%s\"," \
			"\n\tea_texture:\"%s\"," \
			"\n\tsprite_texture:\"%s\"," \
			"\n\tsky_color:%#x," \
			"\n\tfloor_color:%#x" \
			"\n\tmap: %dx%d\n\t",
			config->requested_width, config->requested_height,
			config->north_texture_path, config->south_texture_path,
			config->west_texture_path, config->east_texture_path,
			config->sprite_texture_path, config->sky_color, config->floor_color,
			config->columns, config->rows
		);
		i = 0;
		while (i < config->rows)
		{
			j = 0;
			while (j < config->columns)
				printf("%c ", config->map[(i * config->columns) + j++]);
			if (i == config->rows - 1)
				printf("\n");
			else
				printf("\n\t");
			i++;
		}
		printf("}\n");
	}
	else
		printf("Error:\nInvalid configuration file.\n");
	/*if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
		return (EXIT_FAILURE);
	mlx_mouse_hook (data.mlx_win, &draw_pixel, (void*)&data);
	mlx_key_hook (data.mlx_ptr, &handle_key, (void*)&data);
	mlx_loop(data.mlx_ptr); */
	return (EXIT_SUCCESS);
}
