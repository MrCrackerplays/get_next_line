/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 17:22:29 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/02 16:56:41 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "unistd.h"

int	get_next_line(int fd, char **line)
{
	static t_string_buffer	*buff;
	ssize_t					ret;
	char					temp[BUFFER_SIZE + 1];

	if (line == NULL)
		return (-1);
	buff = malloc(sizeof(t_string_buffer));
	buff->next = NULL;
	ret = read(fd, temp, BUFFER_SIZE);
	buff->str = temp;
	while (ret > 0 && temp == -1)
	{
		sleep(1);
		write(1, &buff, BUFFER_SIZE);
		write(1, "\n", 1);
		ret = read(fd, temp, BUFFER_SIZE);
	}
	return (ret);
}
