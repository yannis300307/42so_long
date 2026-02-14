/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:14:09 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/12 17:18:27 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	add_tile_to_atlas(t_app *app, char *path)
{
	int			width;
	int			height;
	mlx_image	img;

	img = mlx_new_image_from_file(app->ctx, path, &width, &height);
	if (img == MLX_NULL_HANDLE)
		error_exit(app, "Cannot load tile image.");
	if (img != MLX_NULL_HANDLE && (width != 16 || height != 16))
	{
		mlx_destroy_image(app->ctx, img);
		error_exit(app, "Wrong tile size.");
	}
	app->tile_atlas.atlas[app->tile_atlas.size++] = img;
	return (true);
}

void	clear_tile_atlas(t_app *app)
{
	unsigned int	index;

	index = 0;
	while (index < app->tile_atlas.size)
	{
		mlx_destroy_image(app->ctx, app->tile_atlas.atlas[index]);
		index++;
	}
	app->tile_atlas.size = 0;
	free(app->tile_atlas.atlas);
}

void	clear_sprite_atlas(t_app *app)
{
	unsigned int	index;

	index = 0;
	while (index < app->sprite_atlas.size)
	{
		mlx_destroy_image(app->ctx,
			app->sprite_atlas.atlas[index].sprite_sheet);
		index++;
	}
	app->sprite_atlas.size = 0;
	free(app->sprite_atlas.atlas);
}

bool	add_sprite_to_atlas(t_app *app, char *sprite_sheet,
		unsigned int frame_count, double frame_delay)
{
	t_sprite	sprite;

	sprite.sprite_sheet = mlx_new_image_from_file(app->ctx, sprite_sheet,
			&sprite.frame_size.x, &sprite.frame_size.y);
	if (!sprite.sprite_sheet)
		error_exit(app, "Memory allocation error in add_sprite_to_atlas.");
	if (sprite.frame_size.x % frame_count)
		error_exit(app, "Invalid number of frames in spritesheet.");
	sprite.frame_size.x /= frame_count;
	sprite.frame_count = frame_count;
	sprite.frame_delay = frame_delay;
	sprite.frame_timer = frame_delay;
	sprite.frame_index = 0;
	app->sprite_atlas.atlas[app->sprite_atlas.size++] = sprite;
	return (true);
}
