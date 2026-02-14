/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:30:59 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/12 16:41:04 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	add_one_move(t_app *app)
{
	app->player.progress = 0.0;
	if (app->moves_count < 0xffffffff)
		app->moves_count++;
	else
	{
		ft_printf("Can you stop moving and leave the game please? ");
		ft_printf("I can't keep up!\n");
	}
	ft_printf("Move count: %d\n", app->moves_count);
}

void	restore_map(t_app *app)
{
	t_iterator	iterator;
	t_coin		*coin;

	player_teleport(app, app->player.game_start_tile_pos);
	app->moves_count = 0;
	app->collected_croquettes_count = 0;
	iterator = iterator_new(app->coins, 0);
	coin = (t_coin *)iterator_next(&iterator);
	while (coin)
	{
		coin->collected = false;
		coin = (t_coin *)iterator_next(&iterator);
	}
}

void	loose(t_app *app)
{
	restore_map(app);
	app->player.immunity_timer = 5.0;
	app->transition_state = state_open;
}
