/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 17:21:17 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/09 16:11:12 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include "unistd.h"

typedef	struct	s_string_buffer
{
	size_t					depth;
	char					*str;
	struct s_string_buffer	*next;
}				t_string_buffer;
off_t			find_newline(char *str);
t_string_buffer	*get_last(t_string_buffer *buff);
int				get_next_line(int fd, char **line);
int				cleanup(t_string_buffer **buff);
char			*combine_string(t_string_buffer *buff, size_t dpt, off_t pos);
#endif
