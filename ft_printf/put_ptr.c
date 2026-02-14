/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:05:46 by marvin            #+#    #+#             */
/*   Updated: 2025/11/05 22:32:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_ptr(void *ptr, int *error)
{
	int	size;

	if (!ptr)
		return (ft_putstr("(nil)", error));
	size = ft_putstr("0x", error);
	size += puthex((size_t)ptr, 0, error);
	return (size);
}
