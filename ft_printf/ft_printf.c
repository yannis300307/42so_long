/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:09:18 by marvin            #+#    #+#             */
/*   Updated: 2026/02/05 15:59:45 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c, int *error)
{
	int	ret_code;

	if (*error)
		return (-1);
	ret_code = write(1, &c, 1);
	if (ret_code != 1)
		*error = 1;
	return (ret_code);
}

static int	parse_char(char c, va_list args, int *error)
{
	if (c == '%')
		return (ft_putchar('%', error));
	if (c == 's')
		return (ft_putstr(va_arg(args, const char *), error));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int), error));
	if (c == 'c')
		return (ft_putchar((char)va_arg(args, int), error));
	if (c == 'x')
		return (puthex(va_arg(args, unsigned int), 0, error));
	if (c == 'X')
		return (puthex(va_arg(args, unsigned int), 1, error));
	if (c == 'p')
		return (put_ptr(va_arg(args, void *), error));
	if (c == 'u')
		return (ft_put_unsigned_nbr(va_arg(args, unsigned int), error));
	return (0);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (!n)
		return (0);
	while (((char *)s1)[index] == ((char *)s2)[index] && index < n - 1)
		index++;
	return (((unsigned char *)s1)[index] - ((unsigned char *)s2)[index]);
}

int	ft_printf(const char *format, ...)
{
	size_t	index;
	int		size;
	va_list	args;
	int		error;

	error = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	if (!ft_memcmp(format, "%s\n", 4))
		return (ft_put(va_arg(args, const char *), &error));
	size = 0;
	index = 0;
	while (format[index])
	{
		if (format[index] == '%')
			size += parse_char(format[++index], args, &error);
		else
			size += ft_putchar(format[index], &error);
		index++;
	}
	va_end(args);
	if (error)
		return (-1);
	return (size);
}
