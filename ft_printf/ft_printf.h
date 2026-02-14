/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:14:48 by marvin            #+#    #+#             */
/*   Updated: 2025/11/07 13:10:18 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

int	ft_put(const char *s, int *error);
int	ft_putstr(const char *s, int *error);

int	ft_putnbr(int n, int *error);
int	ft_put_unsigned_nbr(unsigned int n, int *error);

int	puthex(size_t n, int upper, int *error);

int	put_ptr(void *ptr, int *error);

int	ft_putchar(char c, int *error);

int	ft_printf(const char *format, ...)__attribute__((format(printf, 1, 2)));

#endif