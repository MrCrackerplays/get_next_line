/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:10:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/04/14 14:07:48 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "unistd.h"
#include "stdlib.h"

ssize_t	starts_with(char *str, char chr)
{
	if (str == NULL || str[0] != chr)
		return (0);
	return (1);
}

ssize_t	find_line(int fd, char **buff, char **line)
{
	char	temp_buffer[BUFFER_SIZE + 1];
	int		i;
	ssize_t	bytes;

	bytes = starts_with(buff[0], '\n');
	i = 0;
	while (buff[0][i] != '\n')
	{
		if (buff[0][i] == '\0')
		{
			bytes = read(fd, &(temp_buffer[0]), BUFFER_SIZE);
			temp_buffer[bytes] = '\0';
			str_join(buff, &(temp_buffer[0]), 0);
			if (bytes < 1)
				break ;
		}
		else
			i++;
		if (bytes == 0)
			bytes = 1;
	}
	line[0] = ft_strndup(buff[0], i);
	str_join(buff, NULL, i + 1);
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
		str_join(buff, &(temp_buffer[0]), 0);
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
