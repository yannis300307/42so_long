/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:31:34 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/13 14:37:05 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	place_static_decorations(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->current_map.size.y)
	{
		x = 0;
		while (x < app->current_map.size.x)
		{
			if (map_get(app, x, y) <= -1 && is_solid(map_get(app, x, y + 1))
				&& map_get(app, x, y + 1) != 5 && get_rand() > 0x55ffffff)
				app->current_map.data[x + y * app->current_map.size.x] = 9
					+ get_rand() % 6;
			x++;
		}
		y++;
	}
}
