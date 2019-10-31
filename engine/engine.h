/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:55:59 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 13:47:29 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "mlx/mlx.h"
# include "config/config.h"

typedef	struct	s_window
{
	void		*ptr;
	void		*win;
	int			width;
	int			height;
}				t_window;

typedef struct	s_camera
{
	int	x;
	int	y;
	int	angle;
}				t_camera;

t_camera		*new_camera(t_config *config);

t_window		*new_window(t_config *config);

#endif
