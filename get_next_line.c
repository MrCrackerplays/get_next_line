/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:10:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/03/10 17:45:03 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "unistd.h"
#include "stdlib.h"

// t_str_buffer	*new_buffer(int depth, char *str)
// {
// 	t_str_buffer	*buff;
// 	ssize_t			i;

// 	if (str == NULL)
// 		return (NULL);
// 	buff = malloc(sizeof(t_str_buffer));
// 	if (buff == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	buff->str = malloc((i + 1) * sizeof(char));
// 	if (buff->str == NULL)
// 	{
// 		free(buff);
// 		return (NULL);
// 	}
// 	while (i >= 0)
// 	{
// 		buff->str[i] = str[i];
// 		i--;
// 	}
// 	buff->depth = depth;
// 	buff->next = NULL;
// 	return (buff);
// }

ssize_t	find_line(int fd, char **buff, char **line)
{
	char	temp_buffer[BUFFER_SIZE + 1];
	int		i;
	ssize_t	bytes;

	if (buff[0][0] == '\n')
		bytes = 1;
	else
		bytes = 0;
	i = 0;
	while (buff[0][i] != '\n')
	{
		if (buff[0][i] == '\0')
		{
			bytes = read(fd, &temp_buffer[0], BUFFER_SIZE);
			if (bytes == 0)
				break ;
			temp_buffer[bytes] = '\0';
			str_join(buff, &temp_buffer[0], 0);
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
{
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
