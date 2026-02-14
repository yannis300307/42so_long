/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:35:36 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/13 15:01:55 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	tile_player_rel(t_app *app, int x, int y)
{
	t_vec2d	pos;

	pos = app->player.tile_pos;
	if (pos.x + x > app->current_map.size.x || pos.x + x < 0 || pos.y
		+ y > app->current_map.size.y || pos.y + y < 0)
		return (-1);
	return (map_get(app, pos.x + x, pos.y + y));
}

static void	check_coin_collect(t_app *app)
{
	t_iterator	iterator;
	t_coin		*coin;

	iterator = iterator_new(app->coins, 0);
	coin = (t_coin *)iterator_next(&iterator);
	while (coin)
	{
		if (coin->tile_pos.x == app->player.tile_pos.x
			&& coin->tile_pos.y == app->player.tile_pos.y && !coin->collected)
		{
			app->collected_croquettes_count++;
			ft_printf("Croquettes collected: %d/%d\n",
				app->collected_croquettes_count, app->coins->size);
			if (app->game_mode == game_mode_bonus)
				croquette_part(app, (t_vec2d){coin->tile_pos.x * 16 + 8,
					coin->tile_pos.y * 16 + 8}, 20);
			coin->collected = true;
		}
		coin = (t_coin *)iterator_next(&iterator);
	}
}

static void	check_end(t_app *app)
{
	if (app->transition_state == state_running
		&& app->player.tile_pos.x == app->tile_end_pos.x
		&& app->player.tile_pos.y == app->tile_end_pos.y
		&& app->transition_state != state_end
		&& app->collected_croquettes_count == app->coins->size)
	{
		app->player.immunity_timer = 10.;
		app->transition_state = state_end;
		if (app->game_mode == game_mode_mandatory)
		{
			ft_printf(
				"Well done! Now play the game with the bonus activated!\n");
			clean_exit(app, 0);
		}
		else
		{
			spawn_confetti(app, (t_vec2d){app->player.target_pos.x + 8,
				app->player.target_pos.y + 2}, 100);
		}
	}
}

void	update_player(t_app *app, double delta)
{
	if (app->player.progress <= 0.0)
		app->player.target_pos = (t_vec2d){app->player.tile_pos.x * 16,
			app->player.tile_pos.y * 16};
	app->player.pos.x = ease_inout_range(app->player.start_pos.x,
			app->player.target_pos.x, app->player.progress);
	app->player.pos.y = ease_inout_range(app->player.start_pos.y,
			app->player.target_pos.y, app->player.progress);
	app->player.progress += delta * app->player.smooth;
	app->cam.pos = (t_vec2d){app->player.pos.x + 8, app->player.pos.y + 8};
	if (app->player.progress > 1.0)
	{
		app->player.progress = 1.0;
		app->player.start_pos = app->player.target_pos;
	}
	if (app->player.progress < 1.0 || array_any(app->pressed_keys, 4))
		app->player.state = walk;
	else
		app->player.state = idle;
	check_coin_collect(app);
	if (app->player.immunity_timer > 0.0)
		app->player.immunity_timer -= delta;
	check_end(app);
}

void	player_teleport(t_app *app, t_vec2d tile_pos)
{
	app->player.tile_pos = tile_pos;
	app->player.pos = (t_vec2d){app->player.tile_pos.x * 16,
		app->player.tile_pos.y * 16};
	app->player.target_pos = app->player.pos;
	app->player.start_pos = app->player.pos;
}
