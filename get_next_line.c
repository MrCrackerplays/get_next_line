/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 17:22:29 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/05 14:00:02 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "unistd.h"
#include "stdlib.h"

t_string_buffer	*get_last(t_string_buffer *buff)
{
	while (buff->next != NULL)
		buff = buff->next;
	return (buff);
}

void test(char *s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	write(1, s, i);
}

int				cleanup(t_string_buffer **buff)
{
	if ((*buff)->next != NULL)
		cleanup(&((*buff)->next));
	free((*buff)->str);
	free((*buff)->next);
	free(*buff);
	*buff = NULL;
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	static t_string_buffer	*buff;
	ssize_t					ret;
	char					temp_str[BUFFER_SIZE + 1];
	t_string_buffer			*relative;

	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
		temp_str[BUFFER_SIZE] = 0;
	ret = read(fd, temp_str, BUFFER_SIZE);
	if (buff == NULL)
	{
		buff = malloc(sizeof(t_string_buffer));
		if (buff == NULL)
			return (-1);
		buff->next = NULL;
	}
	relative = get_last(buff);
	relative->str = temp_str;
	write(1, "8", 1);
	if (ret > 0)
		write(1, "7", 1);
	while (ret > 0)
	{
  		sleep(1);
		test(temp_str);
		relative->next = malloc(sizeof(t_string_buffer));
		if (relative->next == NULL)
			return (cleanup(&buff));
		relative->str = temp_str;
		write(1, "6", 1);
		ret = read(fd, temp_str, BUFFER_SIZE);
	}
	return (ret);
}
