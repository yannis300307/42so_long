/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:59:48 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/13 14:33:13 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	update(void *param)
{
	double	delta;
	t_app	*app;

	app = param;
	delta = 1.0 / (double)TARGET_FPS;
	mlx_clear_window(app->ctx, app->win, (mlx_color){.rgba = 0x000000FF});
	clear_fb(app);
	handle_keys(app, delta);
	app->cam.zoom_lvl = ease_inout_range(app->cam.start_zoom,
			app->cam.target_zoom, app->cam.zoom_progress);
	app->cam.zoom_progress += delta * CAM_SMOOTH;
	if (app->cam.zoom_progress > 1.0f)
	{
		app->cam.zoom_progress = 1.0f;
		app->cam.start_zoom = app->cam.target_zoom;
	}
	update_player(app, delta);
	update_mice(app, delta);
	update_sprites_timings(app, delta);
	update_transition(app, delta);
	update_particles(app, delta);
	draw_everything(app);
}

void	window_hook(int event, void *app)
{
	if (event == 0)
		mlx_loop_end(((t_app *)app)->ctx);
}

static void	error_no_free(const void *msg)
{
	write(2, "Error\n", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		error_no_free("The number of arguments is incorrect.");
	if (!map_check_extension(argv[1]))
		error_no_free("The extension of the map file is incorrect.");
	app.game_mode = game_mode_bonus;
	app = init_app(game_mode_bonus);
	app.current_map = (t_map){0};
	app.current_map = load_map(&app, argv[1]);
	map_check_boundaries(&app);
	check_needed_tiles(&app);
	map_check(&app, &app.current_map);
	spawn_mice(&app);
	spawn_coins(&app);
	place_static_decorations(&app);
	load_tiles(&app);
	load_sprites(&app);
	mlx_set_fps_goal(app.ctx, TARGET_FPS);
	mlx_on_event(app.ctx, app.win, MLX_KEYDOWN, key_hook_down, &app);
	mlx_on_event(app.ctx, app.win, MLX_KEYUP, key_hook_up, &app);
	mlx_on_event(app.ctx, app.win, MLX_WINDOW_EVENT, window_hook, &app);
	mlx_add_loop_hook(app.ctx, update, &app);
	mlx_loop(app.ctx);
	clean_exit(&app, 0);
}
