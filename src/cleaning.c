/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:01:37 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/14 02:27:46 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	clean_exit(t_app *app, int exit_code)
{
	if (app->coins)
		list_clear_and_free(app->coins, free);
	if (app->frame_buffer)
		free(app->frame_buffer);
	clear_tile_atlas(app);
	clear_sprite_atlas(app);
	if (app->mice)
		list_clear_and_free(app->mice, free);
	if (app->current_map.data)
		free(app->current_map.data);
	if (app->frame_buffer_img != MLX_NULL_HANDLE)
		mlx_destroy_image(app->ctx, app->frame_buffer_img);
	if (app->ctx && app->win)
		mlx_destroy_window(app->ctx, app->win);
	if (app->ctx)
		mlx_destroy_context(app->ctx);
	free(app->pressed_keys);
	free(app->pressed_keys_timer);
	free(app->vfx_fb);
	if (app->particles)
		list_clear_and_free(app->particles, free);
	exit(exit_code);
}

void	error_exit(t_app *app, char *error_msg)
{
	write(2, "Error\n", 7);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
	clean_exit(app, 1);
}
