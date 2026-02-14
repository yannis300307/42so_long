/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:23:24 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/13 14:56:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	map_get(t_app *app, int x, int y)
{
	return (app->current_map.data[x + y * app->current_map.size.x]);
}

size_t	get_row_len(const void *line)
{
	size_t	size;

	size = ft_strlen((char *)line);
	if (((char *)line)[size - 1] == '\n')
		size -= 1;
	return (size);
}

static void	add_coin(t_app *app, t_vec2d tile_pos)
{
	t_coin	*coin;

	coin = malloc(sizeof(t_coin));
	if (!coin)
		error_exit(app, "Allocation error in add_coin.");
	coin->tile_pos = tile_pos;
	coin->collected = false;
	if (!list_push_back(app->coins, coin))
	{
		free(coin);
		error_exit(app, "Memory allocation error in add_coin.");
	}
}

bool	is_solid(int type)
{
	if (type < 0)
		return (false);
	return ("11111111\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"[type]);
}

void	spawn_coins(t_app *app)
{
	int	x;
	int	y;

	x = 0;
	while (x < app->current_map.size.x)
	{
		y = 0;
		while (y < app->current_map.size.y)
		{
			if (map_get(app, x, y) == -2)
				add_coin(app, (t_vec2d){x, y});
			y++;
		}
		x++;
	}
}
