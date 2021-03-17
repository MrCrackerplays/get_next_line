/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:10:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/03/17 17:59:59 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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

char	*get_buff(int fd, t_string_buffer *buffer_list)
{
	char	*buff;

	if (buffer_list == NULL)
		return (NULL);
	if (buffer_list->fd < fd)
	{
		if (buffer_list->next == NULL)
			buffer_list->next = create_string_buffer(fd, NULL);
		else if (buffer_list->next->fd > fd)
			buffer_list-> next = create_string_buffer(fd, buffer_list->next);
	}
	if (buffer_list->fd == fd)
		return (&(buffer_list->buff));
	buff = get_buff(fd, buffer_list->next);
	if (buff == NULL)
		buffer_list->next = create_string_buffer(fd, NULL);
	return (buff);
	//dit werkt niet omdat ik de buff als NULL ga returnen wanneer malloc niet lukt, denk ik plus het zit in de knoop met zichzelf
	//TODO: fix deze functie
}

int	get_next_line(int fd, char **line)
{
	static t_string_buffer	*buffer_list;
	char					**buff;
	char					temp_buffer[BUFFER_SIZE + 1];
	ssize_t					bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (buffer_list == NULL)
		buffer_list = create_string_buffer(fd, NULL);
	buff = get_buff(fd, buffer_list);
	bytes = setup_buff(buff, fd, &temp_buffer[0]);
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
		return (0);
	bytes = find_line(fd, buff, line);
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
		return (0);
	return (1);
}
