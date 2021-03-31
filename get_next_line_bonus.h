/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:12:00 by pdruart       #+#    #+#                 */
/*   Updated: 2021/03/31 16:21:29 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include "stddef.h"

typedef struct s_string_buffer
{
	size_t					fd;
	char					*buff;
	struct s_string_buffer	*next;
}				t_string_buffer;
t_string_buffer	*create_string_buffer(int fd, t_string_buffer *next);
int				get_next_line(int fd, char **line);
int				ft_strlen(const char *str);
char			*ft_strndup(const char *str, size_t n);
void			str_join(char **original, char *addition, size_t offset);
#endif
