/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:56:20 by marvin            #+#    #+#             */
/*   Updated: 2025/11/05 22:32:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put(const char *s, int *error)
{
	int	size;

	size = 0;
	while (*s)
	{
		ft_putchar(*(s++), error);
		size++;
	}
	size += ft_putchar('\n', error);
	return (size);
}

int	ft_putstr(const char *s, int *error)
{
	int	size;

	size = 0;
	if (!s)
		return (ft_putstr("(null)", error));
	while (*s)
	{
		ft_putchar(*(s++), error);
		size++;
	}
	return (size);
}
