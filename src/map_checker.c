/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:36:31 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/12 18:18:30 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	map_check_extension(char *name)
{
	size_t	size;

	size = ft_strlen(name);
	if (size < 4)
		return (false);
	if (name[size - 1] != 'r' || name[size - 2] != 'e' || name[size - 3] != 'b'
		|| name[size - 4] != '.')
		return (false);
	return (true);
}

static void	list_add_or_error(t_app *app, t_list *list, t_vec2d vec,
		int *scanned_map)
{
	t_vec2d	*cell_vec;

	scanned_map[vec.x + vec.y * app->current_map.size.x] = 1;
	cell_vec = malloc(sizeof(t_vec2d));
	if (!cell_vec)
	{
		free(scanned_map);
		list_clear_and_free(list, free);
		error_exit(app, "Memory allocation failed in map_check.");
	}
	*cell_vec = vec;
	if (!list_push_back(list, cell_vec))
	{
		free(scanned_map);
		free(cell_vec);
		list_clear_and_free(list, free);
		error_exit(app, "Memory allocation failed in map_check.");
	}
}

static void	check_cell(t_app *app, t_list *queue, int *scanned_map,
		t_vec2d *cell_vec)
{
	if (!scanned_map[(cell_vec->x + 1) + cell_vec->y * app->current_map.size.x])
		list_add_or_error(app, queue, (t_vec2d){cell_vec->x + 1, cell_vec->y},
			scanned_map);
	if (!scanned_map[(cell_vec->x - 1) + cell_vec->y * app->current_map.size.x])
		list_add_or_error(app, queue, (t_vec2d){cell_vec->x - 1, cell_vec->y},
			scanned_map);
	if (!scanned_map[cell_vec->x + (cell_vec->y + 1) * app->current_map.size.x])
		list_add_or_error(app, queue, (t_vec2d){cell_vec->x, cell_vec->y + 1},
			scanned_map);
	if (!scanned_map[cell_vec->x + (cell_vec->y - 1) * app->current_map.size.x])
		list_add_or_error(app, queue, (t_vec2d){cell_vec->x, cell_vec->y - 1},
			scanned_map);
}

static void	check_elements(t_app *app, int *scanned_map)
{
	int	index;

	index = 0;
	while (index < app->current_map.size.x * app->current_map.size.y)
	{
		if ((app->current_map.data[index] == -2
				|| app->current_map.data[index] == -3)
			&& scanned_map[index] != 1)
		{
			free(scanned_map);
			error_exit(app, "Unreachable coin.");
		}
		index++;
	}
	if (scanned_map[app->tile_end_pos.x + app->tile_end_pos.y
			* app->current_map.size.x] != 1)
	{
		free(scanned_map);
		error_exit(app, "Cannot reach end in map file.");
	}
}

void	map_check(t_app *app, t_map *map)
{
	int		*scanned_map;
	int		index;
	t_list	*queue;
	t_vec2d	*cell_vec;

	scanned_map = ft_calloc(map->size.x * map->size.y, sizeof(int));
	if (!scanned_map)
		error_exit(app, "Memory allocation error in map_check.");
	index = 0;
	while (index++ < map->size.x * map->size.y)
		scanned_map[index - 1] = 2 * is_solid(map->data[index - 1]);
	queue = list_new();
	list_add_or_error(app, queue, (t_vec2d){app->player.tile_pos.x,
		app->player.tile_pos.y}, scanned_map);
	while (queue->size)
	{
		cell_vec = list_pop_front(queue);
		check_cell(app, queue, scanned_map, cell_vec);
		free(cell_vec);
	}
	list_clear_and_free(queue, free);
	check_elements(app, scanned_map);
	free(scanned_map);
}
