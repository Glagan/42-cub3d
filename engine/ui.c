/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:40:14 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/10 15:27:47 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

#define SCALE 6

static int
	case_color(t_game *game, int x, int y)
{
	char	c;

	c = MAP_XY(x, y, game->config);
	if (c == '1' || c == '2')
		return (0x0);
	else if (y == (int)game->camera.pos.y
			&& x == (int)game->camera.pos.x)
		return (0x10CC10);
	else if (c == 'A')
		return (0xCCCCCC);
	return (0xFFFFFF);
}

static void
	draw_minimap(t_game *game, t_window *w, t_pos *start, t_pos *end)
{
	int			i;
	int			j;
	int			color;

	i = 0;
	while (i < game->config.rows)
	{
		j = 0;
		while (j < game->config.columns)
		{
			if ((color = case_color(game, j, i)) >= 0)
			{
				set_pos(start,
					w->size.x - (game->config.columns * 5) - 5 + (j * 5),
					w->size.y - (game->config.rows * 5) - 5 + (i * 5));
				set_pos(end,
					w->size.x - (game->config.columns * 5) + (j * 5),
					w->size.y - (game->config.rows * 5) + (i * 5));
				draw_rectangle(w, start, end, color);
			}
			j++;
		}
		i++;
	}
}

void
	update_ui(t_game *game)
{
	t_window	*w;
	t_pos		start;
	t_pos		end;

	w = &game->window;
	set_pos(&start, 2, w->size.y - 27);
	set_pos(&end, 210, w->size.y - 2);
	draw_rectangle(w, &start, &end, 0xFFFFFF);
	draw_minimap(game, w, &start, &end);
}

void
	write_ui_text(t_game *game)
{
	static char	buf[100];
	t_pos		start;
	int			i;

	i = 0;
	while (i < 100)
		buf[i++] = 0;
	if (game->to_collect > 0 && game->to_collect == game->collected)
		ft_write_str(buf, "GG !", 0);
	else if (game->to_collect > 0)
	{
		i = ft_write_str(buf, "Collect: ", 0);
		i = ft_write_str(buf, " / ", ft_write_int(buf, game->collected, i));
		i = ft_write_int(buf, game->to_collect, i);
	}
	else
		ft_write_str(buf, "Nothing to collect !", 0);
	set_pos(&start, 5, game->window.size.y - 25);
	draw_string(&game->window, &start, buf, 0x000000);
}
