/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 17:21:17 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/06 15:46:18 by pdruart       ########   odam.nl         */
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
	char					*str;
	struct s_string_buffer	*next;
}				t_string_buffer;
int				get_next_line(int fd, char **line);
off_t			find_newline(char *str);
#endif
