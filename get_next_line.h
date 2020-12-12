/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:12:00 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/12 11:17:29 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef	struct	s_str_buffer
{
	int					depth;
	char				*str;
	struct s_str_buffer	*next;
}				t_str_buffer;

int				get_next_line(int fd, char **line);
#endif
