/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:06:00 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/13 16:00:19 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	map_check_boundaries(t_app *app)
{
	int	index;

	if (app->current_map.size.x < 3 || app->current_map.size.y < 3)
		error_exit(app, "Map too small.");
	index = 0;
	while (index < app->current_map.size.x)
	{
		if (!is_solid(app->current_map.data[index])
			|| !is_solid(app->current_map.data[index + (app->current_map.size.y
						- 1) * app->current_map.size.x]))
			error_exit(app, "Map must have solid boundaries.");
		index++;
	}
	index = 0;
	while (index < app->current_map.size.y)
	{
		if (!is_solid(app->current_map.data[index * app->current_map.size.x])
			|| !is_solid(app->current_map.data[index * app->current_map.size.x
					+ app->current_map.size.x - 1]))
			error_exit(app, "Map must have solid boundaries.");
		index++;
	}
}

void	check_needed_tiles(t_app *app)
{
	int	index;
	int	player_spawn_found;
	int	end_found;
	int	coin_found;

	index = 0;
	player_spawn_found = 0;
	end_found = 0;
	coin_found = 0;
	while (index < app->current_map.size.x * app->current_map.size.y)
	{
		if (app->current_map.data[index] == 8)
			end_found++;
		else if (app->current_map.data[index] == -3)
			player_spawn_found++;
		else if (app->current_map.data[index] == -2)
			coin_found++;
		index++;
	}
	if (coin_found < 1 || end_found != 1 || player_spawn_found != 1)
		error_exit(app, "Incorrect tiles in map.");
}

void	check_map_shape(t_app *app, t_list *map)
{
	t_iterator		iterator;
	char			*line;
	unsigned int	size;

	iterator = iterator_new(map, 0);
	line = (char *)iterator_next(&iterator);
	size = get_row_len(line);
	while (line)
	{
		if (size != get_row_len(line))
		{
			list_clear_and_free(map, free);
			error_exit(app, "Invalid map shape.");
		}
		line = (char *)iterator_next(&iterator);
	}
}
