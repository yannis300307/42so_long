/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:31:51 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/12 17:23:48 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	init_mlx_and_window(t_app *app)
{
	mlx_window_create_info	info;

	info = (mlx_window_create_info){0};
	info.title = "So Long";
	info.is_resizable = false;
	info.is_fullscreen = true;
	app->ctx = mlx_init();
	if (!app->ctx)
		error_exit(app, "Cannot create mlx context.");
	app->win = mlx_new_window(app->ctx, &info);
	if (!app->win)
		error_exit(app, "Cannot create mlx Window.");
	mlx_get_screen_size(app->ctx, app->win, &app->window_size.x,
		&app->window_size.y);
	mlx_set_font_scale(app->ctx, "assets/font.ttf", app->window_size.y / 20);
}

static void	setup_keys(t_app *app)
{
	app->pressed_keys = ft_calloc(sizeof(bool), 4);
	if (!app->pressed_keys)
		error_exit(app, "Memory allocation error in setup_keys.");
	app->pressed_keys_timer = malloc(sizeof(double) * 4);
	if (!app->pressed_keys_timer)
		error_exit(app, "Memory allocation error in setup_keys.");
	app->pressed_keys_timer[0] = 0.0;
	app->pressed_keys_timer[1] = 0.0;
	app->pressed_keys_timer[2] = 0.0;
	app->pressed_keys_timer[3] = 0.0;
}

static void	app_settings(t_app *app)
{
	app->transition_progress = 1.0;
	app->transition_state = state_open;
	app->collected_croquettes_count = 0;
	app->moves_count = 0;
	if (app->game_mode == game_mode_mandatory)
	{
		app->cam.start_zoom = app->cam.target_zoom;
		app->transition_state = state_running;
	}
}

static void	setup_frame_buffers(t_app *app)
{
	app->frame_buffer = malloc(sizeof(mlx_color) * app->fb_size.x
			* app->fb_size.y);
	app->frame_buffer_img = mlx_new_image(app->ctx, app->fb_size.x,
			app->fb_size.y);
	app->vfx_fb = malloc(app->window_size.x * app->window_size.y
			* sizeof(mlx_color));
}

t_app	init_app(t_game_mode game_mode)
{
	t_app	app;

	app = (t_app){0};
	app.game_mode = game_mode;
	init_mlx_and_window(&app);
	app.tile_atlas = (t_tile_atlas){malloc(sizeof(mlx_image) * TILE_ATLAS_SIZE),
		0};
	app.cam = (t_camera){(t_vec2d){0, 0}, 1.0, 2.0, 0.0, 0.0};
	app.fb_size = (t_vec2d){16 * 28, 16 * 28};
	setup_frame_buffers(&app);
	setup_keys(&app);
	app.sprite_atlas.atlas = malloc(sizeof(t_sprite) * SPRITE_ATLAS_SIZE);
	app.sprite_atlas.size = 0;
	if (!app.frame_buffer || !app.tile_atlas.atlas || !app.sprite_atlas.atlas
		|| !app.frame_buffer_img || !app.vfx_fb)
		error_exit(&app, "Memory allocation error in init_app.");
	app.player = (t_player){(t_vec2d){0, 0}, (t_vec2d){0, 0}, (t_vec2d){0, 0},
		(t_vec2d){0, 0}, (t_vec2d){2, 10}, 0, idle, right, 5, 4, 2, 0, true};
	app.coins = list_new();
	app.mice = list_new();
	app.particles = list_new();
	app_settings(&app);
	if (!app.coins || !app.mice || !app.particles)
		error_exit(&app, "Memory allocation error in init_app.");
	return (app);
}
