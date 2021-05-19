/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:10:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/05/19 17:39:10 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "unistd.h"
#include "stdlib.h"

ssize_t	find_line(int fd, char **buff, char **line)
{
	int		i;
	ssize_t	bytes;

	bytes = buff[0] != NULL && buff[0][0] == '\n';
	i = 0;
	while (buff[0][i] != '\n')
	{
		if (buff[0][i] == '\0')
		{
			bytes = read_into_buff(fd, buff);
			if (bytes < 0)
				return (-1);
			if (bytes == 0)
				break ;
		}
		else
			i++;
		if (bytes == 0)
			bytes = 1;
	}
	line[0] = ft_strndup(buff[0], i);
	if (!str_join(buff, NULL, i + 1, 0))
		return (-1);
	return (bytes);
}

int	setup_buff(char **buff, int fd)
{
	ssize_t	bytes;
	char	temp_buffer[BUFFER_SIZE + 1];

	if (buff == NULL)
		return (-1);
	bytes = 1;
	if (buff[0] == NULL)
	{
		bytes = read(fd, &(temp_buffer[0]), BUFFER_SIZE);
		if (bytes < 0)
			return (-1);
		temp_buffer[bytes] = '\0';
		buff[0] = malloc(sizeof(char));
		if (buff[0] == NULL)
			return (-1);
		buff[0][0] = '\0';
		if (!str_join(buff, &(temp_buffer[0]), 0, ft_strlen(&(temp_buffer[0]))))
			return (-1);
	}
	return (bytes);
}

int	get_next_line(int fd, char **line)
{
	static char	*buff;
	ssize_t		bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	bytes = setup_buff(&buff, fd);
	if (bytes < 0)
		return (-1);
	bytes = find_line(fd, &buff, line);
	if (bytes < 1)
	{
		free(buff);
		buff = NULL;
	}
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
		return (0);
	return (1);
}
