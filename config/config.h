/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:26 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 11:51:10 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <fcntl.h>
# include <unistd.h>
# include "../gnl/get_next_line.h"
# include "../utils/utils.h"

# define DIRECTIONS "NSEW"
# define VALID_MAP_CHARACTERS " 012NSEW"

typedef struct	s_config
{
	int		requested_height;
	int		requested_width;
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	char	*sprite_texture_path;
	int		floor_color;
	int		sky_color;
	int		*map;
	int		rows;
	int		columns;
	int		save_arg;
}				t_config;

t_config		*parse_config(char const *conf_path);

int				count_check_columns(char const *line);

int				check_top_bottom_borders(t_str *map_buffer);

int				check_left_right_borders(t_str *map_buffer);

int				check_valid(t_config *config, t_str *map_buffer);

int				parse_map(t_config *config, t_str *map_buffer);

#endif
