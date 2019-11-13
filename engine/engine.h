/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:55:59 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/13 15:31:22 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>
# include "mlx/mlx.h"
# include "config/config.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_RELEASE	5
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_EXIT			17

# define FLAG_UI			0x00000010
# define FLAG_SHADOWS		0x00000100
# define FLAG_CROSSHAIR		0x00001000
# define FLAG_SAVE			0x00000001

# define BEST_RATIO			1.7777777778

typedef struct	s_raysult
{
	int			column;
	int			row;
	double		distance;
	int			direction;
	int			side;
	int			height;
	t_pos		ray_pos;
	t_pos		ray_dir;
	t_pos		map_pos;
	t_pos		side_dist;
	t_pos		delta_dist;
	t_pos		step;
	double		wall_x;
	t_pos		floor_wall;
	t_pos		c_floor;
}				t_raysult;

typedef struct	s_image
{
	void	*img;
	void	*ptr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_image;

typedef struct	s_tex
{
	char	*path;
	void	*tex;
	void	*ptr;
	t_pos	start;
	t_pos	end;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_tex;

typedef struct	s_sprite_draw
{
	int			sprite_screen;
	t_pos		pos;
	t_pos		transform;
	t_pos		spr_s;
	t_pos		draw_x;
	t_pos		draw_y;
	t_pos		tex_pos;
	int			fact;
	int			draw_y_org;
}				t_sprite_draw;

typedef struct	s_sprite
{
	t_pos			pos;
	double			distance;
	t_tex			*tex;
	struct s_sprite	*next;
	struct s_sprite	*sorted;
}				t_sprite;

typedef	struct	s_window
{
	void		*ptr;
	void		*win;
	t_image		screen;
	t_pos		size;
	t_pos		half;
	double		ratio;
}				t_window;

typedef struct	s_camera
{
	t_pos	pos;
	t_pos	dir;
	t_pos	x_dir;
	t_pos	plane;
}				t_camera;

typedef	struct	s_game
{
	t_config	config;
	t_window	window;
	t_camera	camera;
	t_sprite	*sprites;
	t_tex		tex[TEXTURES];
	t_pos		move;
	t_pos		x_move;
	t_pos		rotate;
	int			options;
	int			to_collect;
	int			collected;
	double		camera_x[1920];
	double		depth[1920];
	double		sf_dist[1080];
	double		cos[2];
	double		sin[2];
}				t_game;

void			find_start_pos(t_config *config, t_camera *camera);

void			find_start_angle(t_config *config, t_camera *camera);

int				move_camera(t_game *game, int direction);

int				move_perp_camera(t_game *game, int direction);

int				rotate_camera(t_game *game, int direction);

int				init_window(t_window *window, t_config *config);

int				clear_window(t_window *window);

void			update_screen(t_game *game);

void			clear_ui(t_window *window);

void			update_ui(t_game *game);

void			write_ui_text(t_game *game);

void			update_window(t_game *game);

int				load_textures(t_game *game);

void			clear_textures(t_game *game);

int				draw_string(t_window *window, t_pos *s_pos, char *str,
					int color);

int				wall_direction(t_raysult *ray);

void			ray_cast(t_game *game, t_raysult *ray, int column);

double			ray_distance(t_game *game, t_raysult *ray);

int				init_image(t_window *window, t_image *img);

void			destroy_image(t_window *window, t_image *img);

void			draw_pixel(t_window *w, t_pos *pos, int color);

int				draw_vertical_line(t_window *window, t_pos *start,
					int length, int color);

int				draw_rectangle(t_window *window, t_pos *p1,
					t_pos *p2, int color);

int				shade_color(int color, double divide);

int				distance_shade(int options, int color, double distance);

int				get_tex_color(t_tex *tex, t_pos *pos);

t_sprite		*add_front_sprite(t_sprite **sprites,
					double distance, t_pos *pos, t_tex *tex);

t_sprite		*add_sorted_sprite(t_sprite **sprites, t_sprite *sprite);

t_sprite		*sort_sprites(t_game *game, t_sprite *sprites);

void			delete_sprite(t_sprite **sprites, t_pos *pos);

void			draw_sprites(t_game *game);

void			clear_sprites(t_sprite **sprites);

void			make_tables(t_game *game);

void			display_crosshair(t_game *game);

void			draw_wall(t_game *game, t_raysult *ray);

void			draw_sky_floor(t_game *game, t_raysult *ray);

void			check_quest(t_game *game);

void			count_items(t_game *game);

#endif
