/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:54:59 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/10 13:46:00 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_sprite
	*add_front_sprite(t_sprite **sprites, double distance, t_pos *pos,
		t_tex *tex)
{
	t_sprite	*new;

	if (!(new = (t_sprite*)malloc(sizeof(*new))))
		return (NULL);
	copy_pos(&new->pos, pos);
	new->distance = distance;
	new->next = *sprites;
	new->tex = tex;
	*sprites = new;
	return (new);
}

t_sprite
	*add_sorted_sprite(t_sprite **sorted, t_sprite *sprite)
{
	t_sprite	*first;
	t_sprite	*previous;

	if (!*sorted)
		return ((*sorted = sprite));
	first = *sorted;
	previous = NULL;
	while (*sorted && sprite->distance < (*sorted)->distance)
	{
		previous = *sorted;
		*sorted = (*sorted)->sorted;
	}
	if (!previous)
	{
		sprite->sorted = *sorted;
		*sorted = sprite;
	}
	else
	{
		sprite->sorted = previous->sorted;
		previous->sorted = sprite;
		*sorted = first;
	}
	return (sprite);
}

t_sprite
	*sort_sprites(t_game *game, t_sprite *sprites)
{
	t_sprite	*sorted;
	t_pos		p;

	sorted = NULL;
	copy_pos(&p, &game->camera.pos);
	while (sprites)
	{
		sprites->distance =
			fabs(((p.x - sprites->pos.x) * (p.x - sprites->pos.x)
				+ (p.y - sprites->pos.y) * (p.y - sprites->pos.y)));
		sprites->sorted = NULL;
		add_sorted_sprite(&sorted, sprites);
		sprites = sprites->next;
	}
	return (sorted);
}

void
	delete_sprite(t_sprite **sprites, t_pos *pos)
{
	t_sprite	*tmp;
	t_sprite	*previous;
	t_sprite	*first;

	first = *sprites;
	previous = NULL;
	while (*sprites)
	{
		if ((int)(*sprites)->pos.x == (int)pos->x
			&& (int)(*sprites)->pos.y == (int)pos->y)
		{
			tmp = *sprites;
			if (!previous)
				*sprites = tmp->next;
			else
				previous->next = tmp->next;
			free(tmp);
			if (previous)
				*sprites = first;
			return ;
		}
		previous = *sprites;
		*sprites = (*sprites)->next;
	}
	*sprites = first;
}

void
	clear_sprites(t_sprite **sprites)
{
	t_sprite	*tmp;

	while (*sprites)
	{
		tmp = (*sprites)->next;
		free(*sprites);
		*sprites = tmp;
	}
	*sprites = NULL;
}
