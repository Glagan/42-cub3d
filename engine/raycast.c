/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:50:30 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/07 12:08:03 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int
	wall_direction(t_raysult *ray)
{
	if (ray->side)
		return ((ray->ray_dir.y < 0) ? (TEX_NORTH) : (TEX_SOUTH));
	return ((ray->ray_dir.x < 0) ? (TEX_WEST) : (TEX_EAST));
}

static void
	init_ray(t_raysult *ray, t_camera *camera, t_pos *mpos, double camera_x)
{
	set_pos(&ray->map_pos, (int)camera->pos.x, (int)camera->pos.y);
	set_pos(&ray->ray_dir, camera->dir.x + camera->plane.x * camera_x,
		                    camera->dir.y + camera->plane.y * camera_x);
	set_pos(&ray->delta_dist, fabs(1. / ray->ray_dir.x), fabs(1. / ray->ray_dir.y));
	if (ray->ray_dir.x < 0)
	{
		set_pos(&ray->step, -1, (ray->ray_dir.y < 0) ? -1 : 1);
		ray->side_dist.x = (ray->ray_pos.x - mpos->x) * ray->delta_dist.x;
	}
	else
	{
		set_pos(&ray->step, 1, (ray->ray_dir.y < 0) ? -1 : 1);
		ray->side_dist.x = (mpos->x + 1. - ray->ray_pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
		ray->side_dist.y = (ray->ray_pos.y - mpos->y) * ray->delta_dist.y;
	else
		ray->side_dist.y = (mpos->y + 1. - ray->ray_pos.y) * ray->delta_dist.y;
}

double
	ray_distance(t_game *game, t_raysult *ray)
{
	if (ray->side)
		return (fabs((ray->map_pos.y - game->camera.pos.y
					+ (1. - ray->step.y) / 2.) / ray->ray_dir.y));
	return (fabs((ray->map_pos.x - game->camera.pos.x
				+ (1. - ray->step.x) / 2.) / ray->ray_dir.x));
}

void
	ray_cast(t_game *game, t_raysult *ray, double camera_x)
{
	int		hit;
	int		next_side;

	copy_pos(&ray->ray_pos, &game->camera.pos);
	init_ray(ray, &game->camera, &ray->map_pos, camera_x);
	hit = 0;
	while (!hit)
	{
		next_side = (ray->side_dist.x < ray->side_dist.y);
		ray->side_dist.x += ((next_side) ? ray->delta_dist.x : 0);
		ray->map_pos.x += ((next_side) ? ray->step.x : 0);
		ray->side_dist.y += ((!next_side) ? ray->delta_dist.y : 0);
		ray->map_pos.y += ((!next_side) ? ray->step.y : 0);
		ray->side = !next_side;
		if (!IN_MAP(ray->map_pos, game->config))
		{
			ray->map_pos.x -= ((!ray->side) ? ray->step.x : 0);
			ray->map_pos.y -= ((ray->side) ? ray->step.y : 0);
			hit = 1;
		}
		/*else if (MAP(ray->map_pos, game->config) == '2')
		{
			add sprite to a sprite queue or something
		}*/
		else if (MAP(ray->map_pos, game->config) == '1')
			hit = 1;
	}
	ray->distance = ray_distance(game, ray);
}
