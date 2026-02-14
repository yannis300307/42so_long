/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:57:52 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/12 17:28:35 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	draw_croquettes_count(t_app *app)
{
	char			*number;
	const mlx_color	color = {.rgba = 0x000000FF};
	int				x;
	const int		char_width = app->window_size.y / 45;

	x = 40;
	mlx_string_put(app->ctx, app->win, x, 80, color, "Croquettes:");
	x += char_width * 9;
	number = ft_itoa(app->collected_croquettes_count);
	if (number)
		mlx_string_put(app->ctx, app->win, x, 80, color, number);
	free(number);
	if (app->collected_croquettes_count)
		x += char_width * (floor(log10(app->collected_croquettes_count)) + 1);
	else
		x += char_width;
	mlx_string_put(app->ctx, app->win, x, 80, color, "/");
	x += char_width;
	number = ft_itoa(app->coins->size);
	if (number)
		mlx_string_put(app->ctx, app->win, x, 80, color, number);
	free(number);
}

void	draw_moves_count(t_app *app)
{
	char			*number;
	const mlx_color	color = {.rgba = 0x000000FF};
	int				x;
	const int		char_width = app->window_size.y / 45;

	x = 40;
	mlx_string_put(app->ctx, app->win, x, 80 + app->window_size.y / 20, color,
		"Moves:");
	x += char_width * 6;
	number = ft_itoa(app->moves_count);
	if (number)
		mlx_string_put(app->ctx, app->win, x, 80 + app->window_size.y / 20,
			color, number);
	free(number);
}

void	draw_moves_count_end_screen(t_app *app)
{
	char			*number;
	const mlx_color	color = {.rgba = 0xFFFFFFFF};
	int				x;
	int				y;
	const int		char_width = app->window_size.y / 60;

	y = app->window_size.y / 2 - (1.0 - ease_inout(app->end_screen_progress))
		* app->window_size.y / 1.8;
	x = (app->window_size.x - char_width * 25) / 2;
	mlx_string_put(app->ctx, app->win, x, y, color, "Map cleared in");
	x += char_width * 15;
	number = ft_itoa(app->moves_count);
	if (number)
		mlx_string_put(app->ctx, app->win, x, y, color, number);
	free(number);
	if (app->moves_count)
		x += char_width * (floor(log10(app->moves_count)) + 2);
	else
		x += (char_width * 2);
	mlx_string_put(app->ctx, app->win, x, y, color, "moves");
	x = (app->window_size.x - char_width * 20) / 2;
	mlx_string_put(app->ctx, app->win, x, app->window_size.y
		+ app->window_size.y / 40 - (app->window_size.y / 20)
		* ease_inout(app->end_screen_progress), color, "Press [esc] to exit");
}

void	draw_hud(t_app *app)
{
	draw_croquettes_count(app);
	draw_moves_count(app);
	if (app->transition_state == state_open
		|| app->transition_state == state_end)
		draw_transition(app, end_ease(app->transition_progress));
	else if (app->transition_state == state_loose)
		draw_transition(app, ease_inout(app->transition_progress));
	else if (app->transition_state == state_finished)
	{
		draw_transition(app, 0.0);
		draw_moves_count_end_screen(app);
	}
}
