/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:12:00 by pdruart       #+#    #+#                 */
/*   Updated: 2021/05/27 13:16:52 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include "stddef.h"

int		get_next_line(int fd, char **line);
int		gnl_strlen(const char *str);
char	*ft_strndup(const char *str, size_t n);
char	*str_join(char **original, char *addition, size_t offset, long j);
long	read_into_buff(int fd, char **buff);
#endif
