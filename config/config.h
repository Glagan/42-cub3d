/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:26 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/10 17:58:51 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <fcntl.h>
# include <unistd.h>
# include "gnl/get_next_line.h"
# include "utils/utils.h"

# define DIRECTIONS "NSEW"
# define VALID_MAP_CHARACTERS " 01234NSEW"

# define FINT(x)			((int)floor(x))
# define CHECK_TOP(p)		(FINT(p.x) >= 0 && FINT(p.y) >= 0)
# define CHECK_BOT(p, c)	(FINT(p.x) < (c).columns && FINT(p.y) < (c).rows)
# define IN_MAP(p, c)		(CHECK_TOP(p) && CHECK_BOT(p, c))
# define MAP(p, c) 			(c).map[(FINT(p.y) * (c).columns) + FINT(p.x)]
# define MAP_XY(x, y, c) 	(c).map[(FINT(y) * (c).columns) + FINT(x)]

# define C_R				0
# define C_NO				1
# define C_SO				2
# define C_WE				3
# define C_EA				4
# define C_S				5
# define C_SU				6
# define C_SC				7
# define C_FT				8
# define C_ST				9
# define C_F				10
# define C_C				11
# define C_MAP				12
# define C_LAST				13

# define TEXTURES			9
# define TEX_NORTH			0
# define TEX_SOUTH			1
# define TEX_WEST			2
# define TEX_EAST			3
# define TEX_SKY			4
# define TEX_FLOOR			5
# define TEX_SPRITE			6
# define TEX_SPRITE_UP		7
# define TEX_SPRITE_C		8

typedef struct	s_config
{
	int			requested_height;
	int			requested_width;
	int			*map;
	int			rows;
	int			columns;
	int			save_arg;
	double		rotate_speed;
	double		move_speed;
	char		*tex_path[TEXTURES];
	unsigned	c[TEXTURES];
	int			set[C_LAST];
	double		fov;
}				t_config;

void			init_config(t_config *config);

int				clear_config(t_config *config);

int				parse_dimensions(t_config *config, char const *line);

int				parse_texture(t_config *config, int key, char const *line);

int				parse_color(t_config *config, int key, char const *line);

int				parse_config(t_config *config, char const *conf_path);

int				count_check_columns(char const *line);

int				check_top_bottom_borders(t_str *map_buffer);

int				check_left_right_borders(t_str *map_buffer);

int				check_valid(t_config *config, t_str *map_buffer);

int				parse_map(t_config *config, t_str *map_buffer);

#endif
