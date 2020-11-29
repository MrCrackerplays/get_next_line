/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 17:22:29 by pdruart       #+#    #+#                 */
/*   Updated: 2020/11/29 14:18:46 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	ssize_t			ret;
	off_t			temp;
	static off_t	off;
	char			buff[BUFFER_SIZE + 1];

	if (line == NULL)
		return (-1);
	buff[BUFFER_SIZE] = '\0';
	temp = -1;
	ret = pread(fd, buff, BUFFER_SIZE, off);
	while (ret == 1 && temp == -1)
	{
		temp = find_newline(buff);
		off += (temp != -1) ? temp : BUFFER_SIZE;
		ret = pread(fd, buff, BUFFER_SIZE, off);
	}
	return (ret);
}
