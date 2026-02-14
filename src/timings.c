/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:30:17 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/05 12:53:08 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	updt_key_timer(t_app *app, double delta, unsigned int index)
{
	if (app->pressed_keys[index])
	{
		if (app->pressed_keys_timer[index] <= 0.0)
		{
			app->pressed_keys_timer[index] = 1.0f;
			return (true);
		}
		app->pressed_keys_timer[index] -= delta * app->player.walk_delay;
	}
	return (false);
}

void	update_sprites_timings(t_app *app, double delta)
{
	unsigned int	index;

	index = 0;
	while (index < app->sprite_atlas.size)
	{
		app->sprite_atlas.atlas[index].frame_timer += delta;
		if (app->sprite_atlas.atlas[index].frame_timer
			> app->sprite_atlas.atlas[index].frame_delay)
		{
			app->sprite_atlas.atlas[index].frame_timer = 0.0;
			app->sprite_atlas.atlas[index].frame_index += 1;
			if (app->sprite_atlas.atlas[index].frame_index
				>= app->sprite_atlas.atlas[index].frame_count)
				app->sprite_atlas.atlas[index].frame_index = 0;
		}
		index++;
	}
}
