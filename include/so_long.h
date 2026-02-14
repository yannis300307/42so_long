/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:23:29 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/13 14:53:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MacroLibX/includes/mlx.h"
# include "../MacroLibX/includes/mlx_extended.h"
# include "../ft_printf/ft_printf.h"
# include "../gnl/get_next_line_bonus.h"
# include "../libft/libft.h"
# include "../list/list.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_ATLAS_SIZE 50
# define SPRITE_ATLAS_SIZE 20
# define CAM_SMOOTH 0.5
# define MOUSE_SMOOTH 2.0
# define TARGET_FPS 60

typedef struct s_vector2d
{
	int				x;
	int				y;
}					t_vec2d;

typedef struct s_vector2d_double
{
	double			x;
	double			y;
}					t_dvec2d;

typedef struct s_particle
{
	t_dvec2d		pos;
	mlx_color		color;
	t_dvec2d		speed;
	double			life_time;
}					t_particle;

typedef struct s_camera
{
	t_vec2d			pos;
	double			start_zoom;
	double			target_zoom;
	double			zoom_progress;
	double			zoom_lvl;
}					t_camera;

typedef struct s_tile_atlas
{
	mlx_image		*atlas;
	unsigned int	size;
}					t_tile_atlas;

typedef struct s_map
{
	int				*data;
	t_vec2d			size;
}					t_map;

typedef enum s_game_mode
{
	game_mode_mandatory,
	game_mode_bonus,
}					t_game_mode;

typedef enum e_player_state
{
	idle,
	walk
}					t_player_state;

typedef enum e_player_dir
{
	right,
	left
}					t_vertical_dir;

typedef struct s_player
{
	t_vec2d			pos;
	t_vec2d			start_pos;
	t_vec2d			target_pos;
	t_vec2d			tile_pos;
	t_vec2d			game_start_tile_pos;
	double			progress;
	t_player_state	state;
	t_vertical_dir	dir;
	double			immunity_timer;
	double			smooth;
	double			walk_delay;
	double			attack_timer;
	bool			attacked;
}					t_player;

typedef struct s_sprite
{
	mlx_image		sprite_sheet;
	t_vec2d			frame_size;
	unsigned int	frame_count;
	double			frame_delay;
	double			frame_timer;
	unsigned int	frame_index;
}					t_sprite;

typedef struct s_sprite_atlas
{
	t_sprite		*atlas;
	unsigned int	size;
}					t_sprite_atlas;

typedef struct s_coin
{
	t_vec2d			tile_pos;
	bool			collected;
}					t_coin;

typedef struct s_mouse
{
	t_vec2d			pos;
	t_vec2d			start_pos;
	t_vec2d			target_pos;
	t_vec2d			tile_pos;
	double			progress;
	bool			dispawn;
	t_vertical_dir	dir;
}					t_mouse;

typedef enum e_game_state
{
	state_open,
	state_running,
	state_end,
	state_loose,
	state_finished,
}					t_transition;

typedef struct s_app
{
	mlx_context		ctx;
	mlx_window		win;
	t_camera		cam;
	t_tile_atlas	tile_atlas;
	mlx_color		*frame_buffer;
	mlx_image		frame_buffer_img;
	t_vec2d			fb_size;
	t_map			current_map;
	bool			*pressed_keys;
	double			*pressed_keys_timer;
	t_sprite_atlas	sprite_atlas;
	t_player		player;
	t_list			*coins;
	t_list			*mice;
	double			transition_progress;
	t_transition	transition_state;
	unsigned int	collected_croquettes_count;
	unsigned int	moves_count;
	t_vec2d			tile_end_pos;
	mlx_color		*vfx_fb;
	t_vec2d			window_size;
	t_list			*particles;
	unsigned int	konami_code_index;
	bool			konami_code_activated;
	double			end_screen_progress;
	t_game_mode		game_mode;
}					t_app;

/* Utils */
bool				array_none(bool *array, unsigned int size);
bool				array_any(bool *array, unsigned int size);
mlx_color			blend_colors(mlx_color a, mlx_color b);
double				ease_bounce_range(double a, double b, double progress);
double				ease_inout_range(double a, double b, double progress);
double				ease_bounce(double progress);
double				ease_inout(double progress);
double				end_ease(double progress);
unsigned int		get_rand(void);

/* Drawing */
void				draw_tile_on_buffer(t_app *app, t_vec2d pos, int atlas_id);

void				draw_sprite_on_buffer(t_app *app, t_vec2d pos, int atlas_id,
						bool x_reversed);

/* Drawing utils */
void				clear_fb(t_app *app);

/* High level drawing */
void				draw_map(t_app *app, bool background);
void				draw_player(t_app *app);
void				draw_croquettes(t_app *app);
void				draw_mice(t_app *app);
void				draw_everything(t_app *app);

/* Timings */
bool				updt_key_timer(t_app *app, double delta,
						unsigned int index);
void				update_sprites_timings(t_app *app, double delta);

/* Player management */
int					tile_player_rel(t_app *app, int x, int y);
void				update_player(t_app *app, double delta);
void				player_teleport(t_app *app, t_vec2d tile_pos);

/* Input handling */
void				handle_keys(t_app *app, double delta);
void				key_hook_up(int key, void *app);
void				key_hook_down(int key, void *app);

/* Mice */
void				update_mice(t_app *app, double delta);
bool				add_mouse(t_app *app, t_vec2d tile_pos);
bool				spawn_mice(t_app *app);

/* Atlas */
bool				add_tile_to_atlas(t_app *app, char *path);
void				clear_tile_atlas(t_app *app);
void				clear_sprite_atlas(t_app *app);
bool				add_sprite_to_atlas(t_app *app, char *sprite_sheet,
						unsigned int frame_count, double frame_delay);

/* Map */
int					map_get(t_app *app, int x, int y);
size_t				get_row_len(const void *line);
bool				is_solid(int type);
void				spawn_coins(t_app *app);

/* Map loader */
t_map				load_map(t_app *app, const char *path);

/* Assets loading */
void				load_tiles(t_app *app);
void				load_sprites(t_app *app);

/* App setup*/
t_app				init_app(t_game_mode game_mode);

/* Cleaning*/
void				clean_exit(t_app *app, int exit_code);
void				error_exit(t_app *app, char *error_msg);

/* Decoration */
void				place_static_decorations(t_app *app);

/* Transition */
void				draw_transition(t_app *app, double progress);
void				update_transition(t_app *app, double delta);

/* Map checker */
bool				map_check_extension(char *name);
void				map_check(t_app *app, t_map *map);
void				map_check_boundaries(t_app *app);
void				check_needed_tiles(t_app *app);
void				check_map_shape(t_app *app, t_list *map);

/* Gameplay */
void				add_one_move(t_app *app);
void				loose(t_app *app);

/* Particles */
void				draw_particles(t_app *app);
void				spawn_confetti(t_app *app, t_vec2d pos,
						unsigned int amount);
void				update_particles(t_app *app, double delta);
void				croquette_part(t_app *app, t_vec2d pos,
						unsigned int amount);

/* Not an easter egg ;-> */
void				konami_code_detector(t_app *app, int keycode);

/* HUD */
void				draw_croquettes_count(t_app *app);
void				draw_moves_count(t_app *app);
void				draw_moves_count_end_screen(t_app *app);
void				draw_hud(t_app *app);

#endif