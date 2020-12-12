/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:10:34 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/12 15:01:11 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "unistd.h"
#include "stdlib.h"

t_str_buffer	*new_buffer(int depth, char *str)
{
	t_str_buffer	*buff;
	ssize_t			i;

	if (str == NULL)
		return (NULL);
	buff = malloc(sizeof(t_str_buffer));
	if (buff == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
		i++;
	buff->str = malloc((i + 1) * sizeof(char));
	if (buff->str == NULL)
	{
		free(buff);
		return (NULL);
	}
	while (i >= 0)
	{
		buff->str[i] = str[i];
		i--;
	}
	buff->depth = depth;
	buff->next = NULL;
	return (buff);
}

int				ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void			str_join(char **original, char *addition)
{
	char	*temp;
	int		i;
	int		j;

	i = ft_strlen(*original);
	j = ft_strlen(addition);
	temp = malloc(i + j + 1);
	if (temp == NULL)
		return (NULL);
	temp[i + j] = '\0';
	while (j >= 0)
	{
		temp[i + j] = addition[j];
		j--;
	}
	if (*original != NULL)
	{
		while (i > 0)
		{
			temp[i - 1] = *original[i - 1];
			i--;
		}
		free(*original);
	}
	*original = temp;
}

ssize_t			find_line(int fd, t_str_buffer **buff, char **line)
{
	t_str_buffer	*relative;
	char			temp_buffer[BUFFER_SIZE + 1];
	int				i;
	ssize_t			bytes;

	relative = *buff;
	bytes = 0;
	while (relative->str[i] != '\n')
	{
		i++;
		if (i == BUFFER_SIZE)
		{
			if (relative->next == NULL)
			{
				bytes = read(fd, &temp_buffer[0], BUFFER_SIZE);
				if (bytes < 1)
					return (bytes < 0 ? -1 : 0);
				temp_buffer[bytes] = '\0';
			}
			i = 0;
			relative = relative->next;
		}
	}
	return (bytes > 0 ? 1 : bytes);
}

int				get_next_line(int fd, char **line)
{
	static t_str_buffer	*buff;
	char				temp_buffer[BUFFER_SIZE + 1];
	ssize_t				bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (buff == NULL)
	{
		bytes = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes < 1)
			return (bytes < 0 ? -1 : 0);
		temp_buffer[bytes] = '\0';
		buff = new_buffer(0, &temp_buffer[0]);
		if (buff == NULL)
			return (-1);
	}
	bytes = find_line(fd, &buff, line);
	if (bytes < 0)
		return (-1);
	return (bytes == 0 ? 0 : 1);
}
