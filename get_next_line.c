/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:10:34 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/12 17:59:20 by pdruart       ########   odam.nl         */
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


ssize_t			find_line(int fd, char **buff, char **line)
{
	char			temp_buffer[BUFFER_SIZE + 1];
	int				i;
	ssize_t			bytes;

	bytes = 0;
	while (*buff[i] != '\n')
	{
		if (*buff[i] == '\0')
			;
		i++;
	}
	return (bytes > 0 ? 1 : bytes);
}

int				get_next_line(int fd, char **line)
{
	static char	*buff;
	char		temp_buffer[BUFFER_SIZE + 1];
	ssize_t		bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (buff == NULL)
	{
		bytes = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes < 1)
			return (bytes < 0 ? -1 : 0);
		temp_buffer[bytes] = '\0';
		buff = malloc(0);
		if (buff == NULL)
			return (-1);
		str_join(&buff, &temp_buffer[0]);
	}
	bytes = find_line(fd, &buff, line);
	if (bytes < 0)
		return (-1);
	return (bytes == 0 ? 0 : 1);
}
