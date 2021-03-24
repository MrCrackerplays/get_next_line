/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:10:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/03/24 16:14:22 by pdruart       ########   odam.nl         */
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
			bytes = read(fd, &temp_buffer[0], BUFFER_SIZE);
			temp_buffer[bytes] = '\0';
			str_join(buff, &temp_buffer[0], 0);
			if (bytes < BUFFER_SIZE)
				break ;
		}
		else
			i++;
		if (bytes == 0)
			bytes = 1;
	}
	*line = ft_strndup(*buff, i);
	str_join(buff, NULL, i + 1);
	return (bytes);
}

int	setup_buff(char **buff, int fd, char *temp_buffer)
{
	ssize_t	bytes;

	bytes = 1;
	if (*buff == NULL)
	{
		bytes = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes == 0)
			return (0);
		if (bytes < 0)
			return (-1);
		temp_buffer[bytes] = '\0';
		*buff = malloc(sizeof(char));
		if (*buff == NULL)
			return (-1);
		**buff = '\0';
		str_join(buff, &temp_buffer[0], 0);
	}
	return (bytes);
}

int	get_next_line(int fd, char **line)
{//TODO ZOOI OMGOOIEN ZODAT DE 0 RETURNED WANNEER EOF IS REACHED + WHATEVER WAS IN DE BUFFER NAAR LINE PLAATSEN, IPV (zoals het nu is) WANNEER EOF IS REACHED DE BUG NAAR LINE PLAATSEN EN 1/bytes RETURNEN EN DAN DE VOLGENDE CALL NIETS IN DE LINE DOEN EN 0 RETURNEN (want 0 bytes returned)
	static char	*buff;
	char		temp_buffer[BUFFER_SIZE + 1];
	ssize_t		bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	bytes = setup_buff(&buff, fd, &temp_buffer[0]);
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
		return (0);
	bytes = find_line(fd, &buff, line);
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
		return (0);
	return (1);
}
