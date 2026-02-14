/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:14:50 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/05 12:44:07 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	tile_put_pixel(t_app *app, t_vec2d source, t_vec2d dest,
		int atlas_id)
{
	mlx_color	color;

	color = mlx_get_image_pixel(app->ctx, app->tile_atlas.atlas[atlas_id],
			source.x, source.y);
	if (color.a > 0)
		app->frame_buffer[dest.x + dest.y * app->fb_size.x] = color;
}

void	draw_tile_on_buffer(t_app *app, t_vec2d pos, int atlas_id)
{
	t_vec2d	source;
	t_vec2d	dest;
	double	ratio;

	ratio = (double)app->window_size.x / (double)app->window_size.y;
	source.y = 0;
	while (source.y < 16)
	{
		dest.y = pos.y - app->cam.pos.y + app->fb_size.y / (app->cam.zoom_lvl
				* 2.0f) + source.y;
		source.x = 0;
		while (source.x < 16)
		{
			dest.x = pos.x - app->cam.pos.x + app->fb_size.x
				/ (app->cam.zoom_lvl * 2.0f) * ratio + source.x;
			if (dest.y >= 0 && dest.y < app->fb_size.y && dest.x >= 0
				&& dest.x < app->fb_size.x)
				tile_put_pixel(app, source, dest, atlas_id);
			source.x++;
		}
		source.y++;
	}
}

static mlx_color	get_pixel(t_app *app, bool x_reversed, int atlas_id,
		t_vec2d coords)
{
	mlx_color	color;

	if (x_reversed)
		color = mlx_get_image_pixel(app->ctx,
				app->sprite_atlas.atlas[atlas_id].sprite_sheet,
				(app->sprite_atlas.atlas[atlas_id].frame_size.x - coords.x - 1)
				+ app->sprite_atlas.atlas[atlas_id].frame_size.x
				* app->sprite_atlas.atlas[atlas_id].frame_index, coords.y);
	else
		color = mlx_get_image_pixel(app->ctx,
				app->sprite_atlas.atlas[atlas_id].sprite_sheet, coords.x
				+ app->sprite_atlas.atlas[atlas_id].frame_size.x
				* app->sprite_atlas.atlas[atlas_id].frame_index, coords.y);
	return (color);
}

static void	sprite_put_pixel(t_app *app, mlx_color color, int dx, int dy)
{
	if (color.a > 0)
	{
		app->frame_buffer[dx + dy * app->fb_size.x] = blend_colors(color,
				app->frame_buffer[dx + dy * app->fb_size.x]);
	}
}

void	draw_sprite_on_buffer(t_app *app, t_vec2d pos, int atlas_id,
		bool x_reversed)
{
	t_vec2d			source;
	t_vec2d			dest;
	mlx_color		color;
	const double	ratio = (double)app->window_size.x / app->window_size.y;

	source.y = 0;
	while (source.y < app->sprite_atlas.atlas[atlas_id].frame_size.y)
	{
		dest.y = pos.y - app->cam.pos.y + app->fb_size.y / (app->cam.zoom_lvl
				* 2.0f) + source.y;
		source.x = 0;
		while (source.x < app->sprite_atlas.atlas[atlas_id].frame_size.x)
		{
			dest.x = pos.x - app->cam.pos.x + app->fb_size.x
				/ (app->cam.zoom_lvl * 2.0f) * ratio + source.x;
			if (dest.y >= 0 && dest.y < app->fb_size.y && dest.x >= 0
				&& dest.x < app->fb_size.x)
			{
				color = get_pixel(app, x_reversed, atlas_id, source);
				sprite_put_pixel(app, color, dest.x, dest.y);
			}
			source.x++;
		}
		source.y++;
	}
}
