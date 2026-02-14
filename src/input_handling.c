/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:34:24 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/05 12:44:07 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	handle_keys(t_app *app, double d)
{
	if (updt_key_timer(app, d, 0) && !is_solid(tile_player_rel(app, -1, 0)))
	{
		app->player.tile_pos.x -= 1;
		add_one_move(app);
	}
	else if (updt_key_timer(app, d, 1) && !is_solid(tile_player_rel(app, 1, 0)))
	{
		app->player.tile_pos.x += 1;
		add_one_move(app);
	}
	else if (updt_key_timer(app, d, 2) && !is_solid(tile_player_rel(app, 0,
				-1)))
	{
		app->player.tile_pos.y -= 1;
		add_one_move(app);
	}
	else if (updt_key_timer(app, d, 3) && !is_solid(tile_player_rel(app, 0, 1)))
	{
		app->player.tile_pos.y += 1;
		add_one_move(app);
	}
}

static void	set_key_state(t_app *app, int index)
{
	app->pressed_keys[index] = true;
	app->pressed_keys_timer[index] = 1.0f;
	add_one_move(app);
}

static bool	check_key(t_app *app, int relat_x, int relat_y)
{
	return (app->transition_state == state_running
		&& array_none(((t_app *)app)->pressed_keys, 4)
		&& ((t_app *)app)->player.progress == 1.0f
		&& !is_solid(tile_player_rel(app, relat_x, relat_y)));
}

void	key_hook_down(int key, void *app)
{
	if (key == 41)
		mlx_loop_end(((t_app *)app)->ctx);
	if (key == 4 && check_key((t_app *)app, -1, 0))
	{
		set_key_state(app, 0);
		((t_app *)app)->player.tile_pos.x -= 1;
		((t_app *)app)->player.dir = left;
	}
	if (key == 7 && check_key((t_app *)app, 1, 0))
	{
		set_key_state(app, 1);
		((t_app *)app)->player.tile_pos.x += 1;
		((t_app *)app)->player.dir = right;
	}
	if (key == 26 && check_key((t_app *)app, 0, -1))
	{
		set_key_state(app, 2);
		((t_app *)app)->player.tile_pos.y -= 1;
	}
	if (key == 22 && check_key((t_app *)app, 0, 1))
	{
		set_key_state(app, 3);
		((t_app *)app)->player.tile_pos.y += 1;
	}
	konami_code_detector(app, key);
}

void	key_hook_up(int key, void *app)
{
	if (key == 4)
		((t_app *)app)->pressed_keys[0] = false;
	if (key == 7)
		((t_app *)app)->pressed_keys[1] = false;
	if (key == 26)
		((t_app *)app)->pressed_keys[2] = false;
	if (key == 22)
		((t_app *)app)->pressed_keys[3] = false;
}
