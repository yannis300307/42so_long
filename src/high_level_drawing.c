/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level_drawing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:28:52 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/09 17:54:17 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	draw_map(t_app *app, bool background)
{
	int	x;
	int	y;
	int	type;

	y = 0;
	while (y < app->current_map.size.y)
	{
		x = 0;
		while (x < app->current_map.size.x)
		{
			if (background)
				draw_tile_on_buffer(app, (t_vec2d){x * 16, y * 16}, 7);
			type = app->current_map.data[x + y * app->current_map.size.x];
			if (!background && type >= 0)
				draw_tile_on_buffer(app, (t_vec2d){x * 16, y * 16}, type);
			x++;
		}
		y++;
	}
}

void	draw_player(t_app *app)
{
	int	offset;

	if (((t_app *)app)->player.dir == right)
		offset = -10;
	else
		offset = -6;
	if (((t_app *)app)->player.state == walk)
		draw_sprite_on_buffer(app, (t_vec2d){((t_app *)app)->player.pos.x
			+ offset, ((t_app *)app)->player.pos.y - 16}, 1,
			((t_app *)app)->player.dir == left);
	else
		draw_sprite_on_buffer(app, (t_vec2d){((t_app *)app)->player.pos.x
			+ offset, ((t_app *)app)->player.pos.y - 16}, 0,
			((t_app *)app)->player.dir == left);
	if (!is_solid(tile_player_rel(app, 0, 1)))
		draw_sprite_on_buffer(app, (t_vec2d){((t_app *)app)->player.pos.x,
			((t_app *)app)->player.pos.y + 14}, 3, false);
}

void	draw_croquettes(t_app *app)
{
	t_iterator	iterator;
	t_coin		*coin;

	iterator = iterator_new(app->coins, 0);
	coin = (t_coin *)iterator_next(&iterator);
	while (coin)
	{
		if (!coin->collected)
		{
			draw_sprite_on_buffer(app, (t_vec2d){coin->tile_pos.x * 16,
				coin->tile_pos.y * 16}, 4, false);
		}
		coin = (t_coin *)iterator_next(&iterator);
	}
}

void	draw_mice(t_app *app)
{
	t_iterator	iterator;
	t_mouse		*mouse;

	iterator = iterator_new(app->mice, 0);
	mouse = (t_mouse *)iterator_next(&iterator);
	while (mouse)
	{
		draw_sprite_on_buffer(app, (t_vec2d){mouse->pos.x, mouse->pos.y}, 5,
			mouse->dir);
		mouse = (t_mouse *)iterator_next(&iterator);
	}
}

void	draw_everything(t_app *app)
{
	double	base_size;

	if (app->window_size.x < app->window_size.y)
		base_size = app->window_size.x;
	else
		base_size = app->window_size.y;
	draw_map(app, true);
	draw_sprite_on_buffer(app, (t_vec2d){48, 96}, 2, false);
	draw_map(app, false);
	draw_player(app);
	draw_mice(app);
	draw_croquettes(app);
	draw_particles(app);
	mlx_set_image_region(app->ctx, app->frame_buffer_img, 0, 0, app->fb_size.x,
		app->fb_size.y, app->frame_buffer);
	mlx_put_transformed_image_to_window(app->ctx, app->win,
		app->frame_buffer_img, 0, 0, base_size / (double)(app->fb_size.x)
		* app->cam.zoom_lvl, base_size / (double)(app->fb_size.y)
		* app->cam.zoom_lvl, 0.0);
	if (app->game_mode == game_mode_bonus)
		draw_hud(app);
}
