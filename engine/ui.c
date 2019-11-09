/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:40:14 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 14:47:50 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

void
	update_ui(t_game *game)
{
	t_window	*w;
	t_pos		start;
	t_pos		end;

	w = &game->window;
	set_pos(&start, 2, w->size.y - 52);
	set_pos(&end, 270, w->size.y - 2);
	draw_rectangle(w, &start, &end, 0x77FFFFFF);
}

void
	write_ui_text(t_game *game)
{
	t_window	*w;
	t_pos		start;
	char		buf[50];

	w = &game->window;
	set_pos(&start, 5, w->size.y - 50);
	sprintf(buf, "x: %lf y: %lf", game->camera.pos.x, game->camera.pos.y);
	draw_string(w, &start, buf, 0x000000);
	set_pos(&start, 5, w->size.y - 25);
	sprintf(buf, "dir: %lfx %lfy", game->camera.dir.x, game->camera.dir.y);
	draw_string(w, &start, buf, 0x000000);
}
