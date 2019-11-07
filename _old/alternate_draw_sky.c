
static void
	draw_sky_floor(t_game *game, int column, t_raysult *ray)
{
	t_pos	floor_wall;
	double	weight;
	t_pos	current_floor;
	t_pos	floor_tex;
	double	current_dist;
	int		i;
	int		j;
	t_pos	pixel;

	j = 0;
	pixel.x = column;
	if (ray->direction == TEX_NORTH)
		set_pos(&floor_wall, ray->map_pos.x + ray->wall_x, ray->map_pos.y + 1.);
	else if (ray->direction == TEX_SOUTH)
		set_pos(&floor_wall, ray->map_pos.x + ray->wall_x, ray->map_pos.y);
	else if (ray->direction == TEX_WEST)
		set_pos(&floor_wall, ray->map_pos.x, ray->map_pos.y + ray->wall_x);
	else if (ray->direction == TEX_EAST)
		set_pos(&floor_wall, ray->map_pos.x + 1., ray->map_pos.y + ray->wall_x);
	i = game->window.half.y + (ray->height / 2.);
	while (i < game->window.size.y)
	{
		current_dist = game->window.size.y / (2. * (double)i - game->window.size.y);
		weight = current_dist / ray->distance;
		set_pos(&current_floor,
			weight * floor_wall.x + (1. - weight) * game->camera.pos.x,
			weight * floor_wall.y + (1. - weight) * game->camera.pos.y);
		set_pos(&floor_tex,
			(int)(current_floor.x * game->tex[TEX_FLOOR].width) % game->tex[TEX_FLOOR].width,
			(int)(current_floor.y * game->tex[TEX_FLOOR].height) % game->tex[TEX_FLOOR].height);
		pixel.y = i;
		draw_pixel_img(&game->window, &pixel, get_tex_color(&game->tex[TEX_FLOOR], &floor_tex));
		pixel.y = j++;
		draw_pixel_img(&game->window, &pixel, get_tex_color(&game->tex[TEX_SKY], &floor_tex));
		i++;
	}
}