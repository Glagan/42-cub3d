/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:54:59 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 13:44:38 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_sprite
	*add_front_sprite(t_sprite **sprites, double distance, t_pos *pos)
{
	t_sprite 	*new;

	if (!(new = (t_sprite*)malloc(sizeof(*new))))
		return (NULL);
	copy_pos(&new->pos, pos);
	new->distance = distance;
	new->next = *sprites;
	*sprites = new;
	return (new);
}

t_sprite
	*add_sorted_sprite(t_sprite **sorted, t_sprite *sprite)
{
	t_sprite	*first;

	if (!*sorted)
		return ((*sorted = sprite));
	first = *sorted;
	while ((*sorted)->sorted && (*sorted)->distance < sprite->distance)
		*sorted = (*sorted)->sorted;
	sprite->sorted = (*sorted)->sorted;
	(*sorted)->sorted = sprite;
	if (first != sprite->sorted)
		*sorted = first;
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
		sprites->distance = ((p.x - sprites->pos.x) * (p.x - sprites->pos.x)
						+ (p.y - sprites->pos.y) * (p.y - sprites->pos.y));
		sprites->sorted = NULL;
		add_sorted_sprite(&sorted, sprites);
		sprites = sprites->next;
	}
	return (sorted);
}
