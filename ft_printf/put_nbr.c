/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:58:48 by marvin            #+#    #+#             */
/*   Updated: 2025/11/05 22:31:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n, int *error)
{
	int	size;

	size = 0;
	if (!n)
		size += ft_putchar('0', error);
	else if (n < 0)
	{
		size += ft_putchar('-', error);
		if (n / 10)
			size += ft_putnbr(-(n / 10), error);
		size += ft_putchar('0' - (n % 10), error);
	}
	else
	{
		if (n / 10)
			size += ft_putnbr(n / 10, error);
		size += ft_putchar('0' + n % 10, error);
	}
	return (size);
}

int	ft_put_unsigned_nbr(unsigned int n, int *error)
{
	int	size;

	size = 0;
	if (!n)
		size += ft_putchar('0', error);
	else
	{
		if (n / 10)
			size += ft_put_unsigned_nbr(n / 10, error);
		size += ft_putchar('0' + n % 10, error);
	}
	return (size);
}
