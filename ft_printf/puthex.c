/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:02:58 by marvin            #+#    #+#             */
/*   Updated: 2025/11/05 22:32:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	get_hex_char(size_t nb, int upper)
{
	if (upper)
		return ("0123456789ABCDEF"[nb]);
	else
		return ("0123456789abcdef"[nb]);
}

int	puthex(size_t n, int upper, int *error)
{
	int		size;
	char	c;

	size = 0;
	if (!n)
		size += ft_putchar('0', error);
	else
	{
		if (n / 16)
			size += puthex(n / 16, upper, error);
		c = get_hex_char(n % 16, upper);
		size += ft_putchar(c, error);
	}
	return (size);
}
