/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_loading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:11:55 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/12 16:24:00 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_tiles(t_app *app)
{
	add_tile_to_atlas(app, "assets/plank_left.png");
	add_tile_to_atlas(app, "assets/plank_single.png");
	add_tile_to_atlas(app, "assets/plank_middle.png");
	add_tile_to_atlas(app, "assets/plank_right.png");
	add_tile_to_atlas(app, "assets/book_stack.png");
	add_tile_to_atlas(app, "assets/floor.png");
	add_tile_to_atlas(app, "assets/ceil.png");
	add_tile_to_atlas(app, "assets/wall_tile.png");
	add_tile_to_atlas(app, "assets/exit.png");
	add_tile_to_atlas(app, "assets/mug.png");
	add_tile_to_atlas(app, "assets/oil_bottle.png");
	add_tile_to_atlas(app, "assets/tomato.png");
	add_tile_to_atlas(app, "assets/tin_can.png");
	add_tile_to_atlas(app, "assets/milk_bottle.png");
	add_tile_to_atlas(app, "assets/cactus_stand.png");
}

void	load_sprites(t_app *app)
{
	add_sprite_to_atlas(app, "assets/cat_idle.png", 2, 0.5f);
	add_sprite_to_atlas(app, "assets/cat_walk.png", 4, 0.15f);
	add_sprite_to_atlas(app, "assets/window.png", 13, 1.0f);
	add_sprite_to_atlas(app, "assets/magic.png", 3, 0.25f);
	add_sprite_to_atlas(app, "assets/croquette.png", 8, 0.15f);
	add_sprite_to_atlas(app, "assets/mouse.png", 4, 0.15f);
}
