/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:50:30 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 13:38:54 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	init_ray(t_raysult *ray, t_camera *camera, t_pos *mpos, double camera_x)
{
	set_pos(&ray->ray_dir,
		camera->dir.x + camera->plane.x * camera_x,
		camera->dir.y + camera->plane.y * camera_x);
	set_pos(&ray->delta_dist,
		fabs(1. / ray->ray_dir.x),
		fabs(1. / ray->ray_dir.y));
	if (ray->ray_dir.x < 0)
	{
		set_pos(&ray->step, -1, (ray->ray_dir.y < 0) ? -1 : 1);
		set_pos(&ray->side_dist,
			(ray->ray_pos.x - mpos->x) * ray->delta_dist.x,
			(ray->ray_dir.y < 0) ? (ray->ray_pos.y - mpos->y) * ray->delta_dist.y
			: (mpos->y + 1. - ray->ray_pos.y) * ray->delta_dist.y);
	}
	else
	{
		set_pos(&ray->step, 1, (ray->ray_dir.y < 0) ? -1 : 1);
		set_pos(&ray->side_dist,
			(mpos->x + 1. - ray->ray_pos.x) * ray->delta_dist.x,
			(ray->ray_dir.y < 0) ? (ray->ray_pos.y - mpos->y) * ray->delta_dist.y
			: (mpos->y + 1. - ray->ray_pos.y) * ray->delta_dist.y);
	}
}

double
	ray_cast(t_game *game, t_raysult *ray, double camera_x)
{
	t_pos	map_pos;
	int		hit;

	set_pos(&map_pos, (int)game->camera->pos.x, (int)game->camera->pos.y);
	copy_pos(&ray->ray_pos, &game->camera->pos);
	init_ray(ray, game->camera, &map_pos, camera_x);
	hit = 0;
	while (!hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			map_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			map_pos.y += ray->step.y;
			ray->side = 1;
		}
		if (map_pos.x < 0 || map_pos.x >= game->config->columns
			|| map_pos.y < 0 || map_pos.y >= game->config->rows)
		{
			if (ray->side)
				map_pos.y -= ray->step.y;
			else
				map_pos.x -= ray->step.x;
			hit = 1;
		}
		else if (MAP(map_pos, game->config) == '1')
			hit = 1;
	}
	if (ray->side)
		return (ray->distance = fabs(
			(map_pos.y - game->camera->pos.y
			+ (1. - ray->step.y) / 2.) / ray->ray_dir.y));
	return (ray->distance = fabs(
		(map_pos.x - game->camera->pos.x
		+ (1. - ray->step.x) / 2.) / ray->ray_dir.x));
}
