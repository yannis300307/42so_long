/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:26:58 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/05 12:44:07 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	clear_fb(t_app *app)
{
	int			x;
	int			y;
	mlx_color	color;

	color.rgba = 0xBBBBBBFF;
	y = 0;
	while (y < app->fb_size.x)
	{
		x = 0;
		while (x < app->fb_size.y)
		{
			app->frame_buffer[x + y * app->fb_size.x] = color;
			x++;
		}
		y++;
	}
}
