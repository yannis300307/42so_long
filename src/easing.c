/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:07:43 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/05 12:44:07 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

double	ease_inout(double progress)
{
	if (progress > 1.0)
		progress = 1.0;
	if (progress < 0.5)
		progress = 2 * progress * progress;
	else
		progress = 1 - powf(-2 * progress + 2, 2) / 2;
	return (progress);
}

double	ease_inout_range(double a, double b, double progress)
{
	return (a + (b - a) * ease_inout(progress));
}

double	ease_bounce(double progress)
{
	const double	n1 = 7.5625;
	const double	d1 = 2.75;
	double			ratio;

	if (progress < 1.0 / d1)
	{
		ratio = (n1 * progress * progress);
	}
	else if (progress < 2.0 / d1)
	{
		progress -= 1.5 / d1;
		ratio = (n1 * progress * progress + 0.75);
	}
	else if (progress < 2.5 / d1)
	{
		progress -= 2.25 / d1;
		ratio = (n1 * progress * progress + 0.9375);
	}
	else
	{
		progress -= 2.625 / d1;
		ratio = (n1 * progress * progress + 0.984375);
	}
	return (ratio);
}

double	end_ease(double progress)
{
	if (progress < 0.4)
		return (ease_inout(progress / 0.4) * 0.8);
	else if (progress < 0.8)
		return (0.8);
	else
		return (ease_inout((progress - 0.8) / 0.2) * 0.2 + 0.8);
}

double	ease_bounce_range(double a, double b, double progress)
{
	return (a + (b - a) * ease_bounce(progress));
}
