/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:26 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/03 16:46:56 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <fcntl.h>
# include <unistd.h>
# include "gnl/get_next_line.h"
# include "utils/utils.h"

# define DIRECTIONS "NSEW"
# define VALID_MAP_CHARACTERS " 012NSEW"

/*# define _P_POS(p)			(int)pos->p
# define MAP_P(pos, conf) 	conf->map[(_P_POS(y) * conf->columns) + _P_POS(x)]*/
# define MAP(p, c) 			c->map[((int)p.y * c->columns) + (int)p.x]
# define MAP_XY(x, y, c) 	c->map[((int)(y) * c->columns) + (int)(x)]

typedef struct	s_config
{
	int			requested_height;
	int			requested_width;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	char		*sprite_texture_path;
	unsigned	floor_color;
	unsigned	sky_color;
	int			*map;
	int			rows;
	int			columns;
	int			save_arg;
	double		fov;
}				t_config;

int				parse_dimensions(t_config *config, char const *line);

int				parse_texture_path(t_config *config, char const *line);

int				parse_sprite_texture(t_config *config, char const *line);

int				parse_color(t_config *config, char const *line);

t_config		*parse_config(char const *conf_path);

int				count_check_columns(char const *line);

int				check_top_bottom_borders(t_str *map_buffer);

int				check_left_right_borders(t_str *map_buffer);

int				check_valid(t_config *config, t_str *map_buffer);

int				parse_map(t_config *config, t_str *map_buffer);

#endif
