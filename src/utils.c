/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:25:45 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/05 12:44:07 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	array_none(bool *array, unsigned int size)
{
	unsigned int	indet;

	indet = 0;
	while (indet < size)
	{
		if (array[indet++])
			return (false);
	}
	return (true);
}

bool	array_any(bool *array, unsigned int size)
{
	unsigned int	indet;

	indet = 0;
	while (indet < size)
	{
		if (array[indet++])
			return (true);
	}
	return (false);
}

mlx_color	blend_colors(mlx_color a, mlx_color b)
{
	mlx_color	merged;

	if (a.a + b.a > 0xFF)
	{
		b.a = 0xFF - a.a;
	}
	merged.a = a.a + b.a;
	merged.r = (a.r * a.a) / 0xFF + (b.r * b.a) / 0xFF;
	merged.g = (a.g * a.a) / 0xFF + (b.g * b.a) / 0xFF;
	merged.b = (a.b * a.a) / 0xFF + (b.b * b.a) / 0xFF;
	return (merged);
}

unsigned int	get_rand(void)
{
	static unsigned int	seed = 0x76a9c5d3;

	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return (seed);
}
