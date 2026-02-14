/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mice.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:11:30 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/09 18:19:03 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	mouse_walk(t_app *app, t_mouse *mouse)
{
	if (mouse->dir == right)
	{
		if (is_solid(map_get(app, mouse->tile_pos.x + 1, mouse->tile_pos.y + 1))
			&& !is_solid(map_get(app, mouse->tile_pos.x + 1,
					mouse->tile_pos.y)))
			mouse->tile_pos.x++;
		else
			mouse->dir = left;
	}
	else if (mouse->dir == left)
	{
		if (is_solid(map_get(app, mouse->tile_pos.x - 1, mouse->tile_pos.y + 1))
			&& !is_solid(map_get(app, mouse->tile_pos.x - 1,
					mouse->tile_pos.y)))
			mouse->tile_pos.x--;
		else
			mouse->dir = right;
	}
}

static void	update_mouse(t_app *app, t_mouse *mouse, double delta)
{
	if (mouse->progress <= 0.0)
		mouse->target_pos = (t_vec2d){mouse->tile_pos.x * 16, mouse->tile_pos.y
			* 16};
	mouse->pos.x = ease_bounce_range(mouse->start_pos.x, mouse->target_pos.x,
			mouse->progress);
	mouse->pos.y = ease_bounce_range(mouse->start_pos.y, mouse->target_pos.y,
			mouse->progress);
	mouse->progress += delta * MOUSE_SMOOTH;
	if (mouse->progress > 1.0f)
	{
		mouse->progress = 0.0;
		mouse->start_pos = mouse->target_pos;
		mouse_walk(app, mouse);
		mouse->target_pos = (t_vec2d){mouse->tile_pos.x * 16, mouse->tile_pos.y
			* 16};
	}
	if (mouse->tile_pos.x == app->player.tile_pos.x
		&& mouse->tile_pos.y == app->player.tile_pos.y
		&& app->player.immunity_timer <= 0.0)
		app->transition_state = state_loose;
}

void	update_mice(t_app *app, double delta)
{
	t_iterator	iterator;
	t_mouse		*mouse;

	if (app->transition_state != state_running)
		return ;
	iterator = iterator_new(app->mice, 0);
	mouse = (t_mouse *)iterator_next(&iterator);
	while (mouse)
	{
		update_mouse(app, mouse, delta);
		mouse = (t_mouse *)iterator_next(&iterator);
	}
}

bool	add_mouse(t_app *app, t_vec2d tile_pos)
{
	t_mouse	*mouse;

	mouse = (t_mouse *)malloc(sizeof(t_mouse));
	if (!mouse)
		return (false);
	mouse->dir = right;
	mouse->tile_pos = tile_pos;
	mouse->progress = 0.0;
	mouse->pos = (t_vec2d){mouse->tile_pos.x * 16, mouse->tile_pos.y * 16};
	mouse->start_pos = mouse->pos;
	mouse->target_pos = mouse->pos;
	mouse->dispawn = false;
	if (!list_push_back(app->mice, mouse))
	{
		free(mouse);
		error_exit(app, "Memory allocation error in add_mouse.");
	}
	return (true);
}

bool	spawn_mice(t_app *app)
{
	int	x;
	int	y;

	x = 0;
	while (x < app->current_map.size.x)
	{
		y = 0;
		while (y < app->current_map.size.y)
		{
			if (map_get(app, x, y) == -1 && is_solid(map_get(app, x, y + 1))
				&& get_rand() > 0xCAFFFFFF)
			{
				if (!add_mouse(app, (t_vec2d){x, y}))
					error_exit(app, "Cannot allocate memory in spawn_mice.");
			}
			y++;
		}
		x++;
	}
	return (false);
}
