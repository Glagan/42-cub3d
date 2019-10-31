/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:25:20 by ncolomer          #+#    #+#             */
/*   Updated: 2019/10/31 16:29:17 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int
	clear_window(t_window *window)
{
	return (mlx_clear_window(window->ptr, window->win));
}

int
	draw_string(t_window *window, t_pos *s_pos, char *str, int color)
{
	return (mlx_string_put(
				window->ptr, window->win,
				s_pos->x, s_pos->y,
				color,
				str)
			);
}
