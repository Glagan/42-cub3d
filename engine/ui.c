/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:40:14 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/09 18:36:01 by ncolomer         ###   ########.fr       */
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
	set_pos(&end, 270, w->size.y - 2);
	draw_rectangle(w, &start, &end, 0x77FFFFFF);
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
	t_window	*w;
	t_pos		start;
	char		buf[50];
	int			i;

	w = &game->window;
	i = 0;
	while (i < 50)
		buf[i++] = 0;
	i = ft_write_int(buf, (int)game->camera.pos.x, 0);
	i = ft_write_str(buf, "x ", i);
	i = ft_write_int(buf, (int)game->camera.pos.y, i);
	i = ft_write_str(buf, "y", i);
	set_pos(&start, 5, w->size.y - 50);
	draw_string(w, &start, buf, 0x000000);
	i = ft_write_str(buf, "Collect: ", 0);
	i = ft_write_int(buf, game->collected, i);
	i = ft_write_str(buf, " / 8", i);
	set_pos(&start, 5, w->size.y - 25);
	draw_string(w, &start, buf, 0x000000);
}
