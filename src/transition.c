/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:05:07 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/12 16:56:45 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	draw_out_line(t_app *app, t_vec2d start, int stop_x,
		mlx_color color)
{
	int	index;

	if (start.x < 0)
		return ;
	if (stop_x >= app->window_size.x)
		stop_x = app->window_size.x - 1;
	if (start.y < 0)
		return ;
	if (start.y >= app->window_size.y)
		return ;
	index = 0;
	while (index < start.x)
	{
		app->vfx_fb[index + start.y * app->window_size.x] = color;
		index++;
	}
	index = stop_x;
	while (index < stop_x + (app->window_size.x - stop_x))
	{
		app->vfx_fb[index + start.y * app->window_size.x] = color;
		index++;
	}
}

static void	draw_full_remaining(t_app *app, int size, mlx_color color,
		t_vec2d center)
{
	int	x;
	int	y;

	y = 0;
	if (size < 0)
		return ;
	if (center.y - size < 0)
		center.y = size;
	while (y < center.y - size)
	{
		x = 0;
		while (x < app->window_size.x)
			app->vfx_fb[(x++) + y * app->window_size.x] = color;
		y++;
	}
	y += size * 2;
	while (y < app->window_size.y)
	{
		x = 0;
		while (x < app->window_size.x)
			app->vfx_fb[(x++) + y * app->window_size.x] = color;
		y++;
	}
}

static void	draw_outside_circle(t_app *app, int size, mlx_color color,
		t_vec2d c)
{
	int	t1;
	int	x;
	int	y;
	int	t2;

	t1 = size / 16;
	x = size;
	y = 0;
	while (x >= y)
	{
		draw_out_line(app, (t_vec2d){c.x - x, c.y - y}, c.x + x, color);
		draw_out_line(app, (t_vec2d){c.x - x, c.y + y}, c.x + x, color);
		draw_out_line(app, (t_vec2d){c.x - y, c.y - x}, c.x + y, color);
		draw_out_line(app, (t_vec2d){c.x - y, c.y + x}, c.x + y, color);
		y++;
		t1 = t1 + y;
		t2 = t1 - x;
		if (t2 >= 0)
		{
			t1 = t2;
			x = x - 1;
		}
	}
	draw_full_remaining(app, size, color, c);
}

void	draw_transition(t_app *app, double progress)
{
	mlx_color	color;
	int			index;

	index = 0;
	if (app->transition_state != state_finished)
	{
		color.rgba = 0x000000ff;
		while (index < app->window_size.x * app->window_size.y)
			app->vfx_fb[index++] = (mlx_color){0x00000000};
		draw_outside_circle(app, (1.0 - progress) * sqrt(pow(app->window_size.x
					/ 2, 2) + pow(app->window_size.y / 2, 2)), color,
			(t_vec2d){app->window_size.x / 2, app->window_size.y / 2});
	}
	else
	{
		color.rgba = 0x000000ff;
		while (index < app->window_size.x * app->window_size.y)
			app->vfx_fb[index++] = color;
	}
	mlx_pixel_put_array(app->ctx, app->win, 0, 0, app->vfx_fb,
		app->window_size.x * app->window_size.y);
}

void	update_transition(t_app *app, double delta)
{
	if (app->transition_progress > 0.0 && app->transition_state == state_open)
		app->transition_progress -= delta * 0.3;
	if (app->transition_progress < 1.0 && app->transition_state == state_end)
		app->transition_progress += delta * 0.3;
	if (app->transition_progress < 1.0 && app->transition_state == state_loose)
		app->transition_progress += delta * 0.8;
	if (app->transition_progress >= 1.0 && app->transition_state == state_loose)
		loose(app);
	if (app->transition_state == state_open && app->transition_progress <= 0.0)
		app->transition_state = state_running;
	if (app->transition_state == state_end && app->transition_progress >= 1.0)
		app->transition_state = state_finished;
	if (app->transition_state == state_finished)
		app->end_screen_progress += delta * 0.8;
	if (app->end_screen_progress > 1.0)
		app->end_screen_progress = 1.0;
}
