/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:40:14 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/10 14:32:44 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void
	update_ui(t_game *game)
{
	t_window	*w;
	t_pos		start;
	t_pos		end;

	w = &game->window;
	set_pos(&start, 2, w->size.y - 52);
	set_pos(&end, 160, w->size.y - 2);
	draw_rectangle(w, &start, &end, 0xFFFFFF);
}

static int
	ft_write_int(char *buf, int val, int start)
{
	int	length;
	int	tmp;

	length = 1;
	tmp = val;
	while (tmp > 9)
	{
		length++;
		tmp /= 10;
	}
	if (val == 0)
		buf[start++] = '0';
	else
	{
		tmp = length;
		while (val > 0)
		{
			buf[start + --tmp] = "0123456789"[val % 10];
			val /= 10;
		}
		start += length;
	}
	buf[start] = 0;
	return (start);
}

static int
	ft_write_str(char *buf, char *str, int start)
{
	int	i;

	i = 0;
	while (str[i])
		buf[start++] = str[i++];
	buf[start] = 0;
	return (start);
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
	i = ft_write_int(buf, (int)game->camera.pos.x, 0);
	i = ft_write_str(buf, "x ", i);
	i = ft_write_int(buf, (int)game->camera.pos.y, i);
	i = ft_write_str(buf, "y", i);
	set_pos(&start, 5, game->window.size.y - 50);
	draw_string(&game->window, &start, buf, 0x000000);
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
