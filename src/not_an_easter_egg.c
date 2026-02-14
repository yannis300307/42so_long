/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_an_easter_egg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:23:36 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/13 14:47:14 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	konami_bonus(t_app *app)
{
	spawn_confetti(app, (t_vec2d){app->player.target_pos.x + 8,
		app->player.target_pos.y + 2}, 100);
	if (!app->konami_code_activated)
	{
		app->player.smooth = 8.0;
		app->player.walk_delay = 8.0;
	}
	else
	{
		app->player.smooth = 4.0;
		app->player.walk_delay = 2.0;
	}
	app->konami_code_activated = !app->konami_code_activated;
	ft_printf("Yay!\n");
}

void	konami_code_detector(t_app *app, int keycode)
{
	const int	code[10] = {26, 26, 22, 22, 4, 7, 4, 7, 5, 20};

	if (app->game_mode == game_mode_mandatory)
		return ;
	if (code[app->konami_code_index] == keycode)
	{
		if (app->konami_code_index == 9)
		{
			konami_bonus(app);
			app->konami_code_index = 0;
		}
		else
			app->konami_code_index++;
	}
	else
		app->konami_code_index = 0;
}
