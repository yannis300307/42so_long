/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:46:47 by yben-dje          #+#    #+#             */
/*   Updated: 2025/12/04 19:47:09 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <malloc.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strjoin(char *dst, const char *src, size_t line_size);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	safe_free(char **pointer);
size_t	ft_strlen(const char *s);
int		contains(char *str, char c);

char	*get_next_line(int fd);

#endif