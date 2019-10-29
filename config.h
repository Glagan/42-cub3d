/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:51:26 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/29 14:09:55 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

#include <fcntl.h>
#include <unistd.h>
#include "gnl/get_next_line.h"
#include "utils/utils.h"

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
	int		**map;
	int		save_arg;
}				t_config;

t_config		*parse_config(char const *conf_path);

#endif
