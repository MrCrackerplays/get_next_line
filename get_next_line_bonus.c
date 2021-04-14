/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:10:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/04/14 12:16:36 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "unistd.h"
#include "stdlib.h"

ssize_t	find_line(int fd, char **buff, char **line)
{
	char	temp_buffer[BUFFER_SIZE + 1];
	int		i;
	ssize_t	bytes;

	bytes = buff[0] != NULL && buff[0][0] == '\n';
	i = 0;
	while (buff[0][i] != '\n')
	{
		if (buff[0][i] == '\0')
		{
			bytes = read(fd, &temp_buffer[0], BUFFER_SIZE);
			temp_buffer[bytes] = '\0';
			str_join(buff, &temp_buffer[0], 0);
			if (bytes < 1)
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

int	setup_buff(char **buff, int fd)
{
	ssize_t	bytes;
	char	temp_buffer[BUFFER_SIZE + 1];

	if (buff == NULL)
		return (-1);
	bytes = 1;
	if (*buff == NULL)
	{
		bytes = read(fd, &temp_buffer[0], BUFFER_SIZE);
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

t_string_buffer	**get_buff(int fd, t_string_buffer **buffer_list)
{
	t_string_buffer	*buff_list;

	if (buffer_list == NULL || (*buffer_list) == NULL)
		return (NULL);
	if ((*buffer_list)->fd > fd)
		(*buffer_list) = create_string_buffer(fd, (*buffer_list));
	buff_list = *buffer_list;
	if (buff_list->fd < fd)
	{
		if (buff_list->next == NULL)
			buff_list->next = create_string_buffer(fd, NULL);
		else if (buff_list->next->fd > fd)
			buff_list->next = create_string_buffer(fd, buff_list->next);
	}
	if (buff_list->fd == fd)
		return (buffer_list);
	return (get_buff(fd, &(*buffer_list)->next));
}

void	clean_fd_buffer(int fd, t_string_buffer **buffer_list)
{
	t_string_buffer	*holder;
	t_string_buffer	*prev;

	if (buffer_list == NULL || buffer_list[0] == NULL)
		return ;
	if (buffer_list[0]->fd == fd)
	{
		holder = buffer_list[0];
		buffer_list[0] = buffer_list[0]->next;
		free(holder->buff);
		free(holder);
		return ;
	}
	prev = buffer_list[0];
	holder = prev->next;
	while (holder != NULL && holder->fd != fd)
	{
		prev = prev->next;
		holder = prev->next;
	}
	if (holder == NULL)
		return ;
	prev->next = holder->next;
	free(holder->buff);
	free(holder);
}

int	get_next_line(int fd, char **line)
{
	static t_string_buffer	*buffer_list;
	char					**buff;
	ssize_t					bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (buffer_list == NULL)
		buffer_list = create_string_buffer(fd, NULL);
	buff = &(*get_buff(fd, &buffer_list))->buff;
	bytes = setup_buff(buff, fd);
	if (bytes >= 0)
		bytes = find_line(fd, buff, line);
	if (bytes < 1 && buff[0][0] == '\0')
	{
		free(*buff);
		*buff = NULL;
		clean_fd_buffer(fd, &buffer_list);
		return (-1 * ((bytes >> (sizeof(bytes) * 8 - 1)) & 1));
	}
	return (1);
}
