/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:50:30 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/06 18:41:30 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void
	init_ray(t_raysult *ray, t_camera *camera, t_pos *mpos, double camera_x)
{
	set_pos(&ray->map_pos, (int)camera->pos.x, (int)camera->pos.y);
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
	ray->direction = (ray->ray_pos.x >= 0);
}

double
	ray_cast(t_game *game, t_raysult *ray, double camera_x)
{
	int		hit;

	copy_pos(&ray->ray_pos, &game->camera.pos);
	init_ray(ray, &game->camera, &ray->map_pos, camera_x);
	hit = 0;
	while (!hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->side = 1;
		}
		if (ray->map_pos.x < 0 || ray->map_pos.x >= game->config.columns
			|| ray->map_pos.y < 0 || ray->map_pos.y >= game->config.rows)
		{
			if (ray->side)
				ray->map_pos.y -= ray->step.y;
			else
				ray->map_pos.x -= ray->step.x;
			hit = 1;
		}
		else if (MAP(ray->map_pos, game->config) == '1')
			hit = 1;
	}
	if (ray->side)
		return (ray->distance = fabs(
			(ray->map_pos.y - game->camera.pos.y
			+ (1. - ray->step.y) / 2.) / ray->ray_dir.y));
	return (ray->distance = fabs(
		(ray->map_pos.x - game->camera.pos.x
		+ (1. - ray->step.x) / 2.) / ray->ray_dir.x));
}
