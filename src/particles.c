/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:44:06 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/13 14:53:30 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	spawn_confetti(t_app *app, t_vec2d pos, unsigned int amount)
{
	t_particle	*particle;
	double		vec_len;

	while (amount--)
	{
		particle = malloc(sizeof(t_particle));
		if (!particle)
			error_exit(app, "Memory allocation error in spawn_confetti.");
		particle->color = (mlx_color)((get_rand() & 0xFFFFFF00) | 0x000000FF);
		particle->pos = (t_dvec2d){pos.x, pos.y};
		particle->speed.x = (((double)get_rand() / 0xffffffff) - 0.5) * 2.0;
		particle->speed.y = (((double)get_rand() / 0xffffffff) - 0.5) * 2.0;
		particle->life_time = (((double)get_rand() / 0xffffffff) - 0.5) * 2.0
			+ 2.0;
		vec_len = sqrt(pow(particle->speed.x, 2) + pow(particle->speed.y, 2));
		particle->speed.x /= vec_len;
		particle->speed.y /= vec_len;
		particle->speed.x *= (((double)get_rand() / 0xffffffff) - 0.5) + 0.5;
		particle->speed.y *= (((double)get_rand() / 0xffffffff) - 0.5) + 0.5;
		if (!list_push_back(app->particles, particle))
		{
			free(particle);
			error_exit(app, "Memory allocation error in spawn_confetti.");
		}
	}
}

void	croquette_part(t_app *app, t_vec2d pos, unsigned int amount)
{
	t_particle	*particle;
	double		vec_len;

	while (amount--)
	{
		particle = malloc(sizeof(t_particle));
		if (!particle)
			error_exit(app, "Memory allocation error in croquette_part.");
		particle->color = (mlx_color)0x955A2DFF;
		particle->pos = (t_dvec2d){pos.x, pos.y};
		particle->speed.x = (((double)get_rand() / 0xffffffff) - 0.5) * 1.0;
		particle->speed.y = (((double)get_rand() / 0xffffffff) - 0.1) * 2.0;
		particle->life_time = (((double)get_rand() / 0xffffffff) - 0.5) * 2.0
			+ 2.0;
		vec_len = sqrt(pow(particle->speed.x, 2) + pow(particle->speed.y, 2));
		particle->speed.x /= vec_len;
		particle->speed.y /= vec_len;
		particle->speed.x *= (((double)get_rand() / 0xffffffff) - 0.5) + 0.5;
		particle->speed.y *= (((double)get_rand() / 0xffffffff) - 0.3) + 0.5;
		if (!list_push_back(app->particles, particle))
		{
			free(particle);
			error_exit(app, "Memory allocation error in croquette_part.");
		}
	}
}

void	update_particles(t_app *app, double delta)
{
	t_iterator		iterator;
	t_particle		*particle;
	unsigned int	index;

	iterator = iterator_new(app->particles, 0);
	particle = (t_particle *)iterator_next(&iterator);
	while (particle)
	{
		particle->pos.x += particle->speed.x * delta * 20.0;
		particle->pos.y += particle->speed.y * delta * 20.0;
		particle->life_time -= delta;
		particle->speed.y += delta * 0.5;
		particle = (t_particle *)iterator_next(&iterator);
	}
	index = 0;
	while (index < app->particles->size)
	{
		particle = list_get_at_index(app->particles, index);
		if (particle->life_time < 0.0)
			list_pop_at_free(app->particles, index--, free);
		index++;
	}
}

void	draw_particles(t_app *app)
{
	t_iterator	iterator;
	t_particle	*particle;
	t_vec2d		dest;
	double		ratio;

	ratio = (double)app->window_size.x / (double)app->window_size.y;
	iterator = iterator_new(app->particles, 0);
	particle = (t_particle *)iterator_next(&iterator);
	while (particle)
	{
		dest.x = (int)particle->pos.x - app->cam.pos.x + app->fb_size.x
			/ (app->cam.zoom_lvl * 2.0f) * ratio;
		dest.y = (int)particle->pos.y - app->cam.pos.y + app->fb_size.y
			/ (app->cam.zoom_lvl * 2.0f);
		if (dest.x >= 0 && dest.y >= 0 && dest.x < app->fb_size.x
			&& dest.y < app->fb_size.y)
			app->frame_buffer[dest.x + dest.y
				* app->fb_size.y] = particle->color;
		particle = (t_particle *)iterator_next(&iterator);
	}
}
