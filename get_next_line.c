/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 17:22:29 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/09 16:48:48 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdlib.h"

void test(char *s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	write(1, s, i);
}

int				get_next_line(int fd, char **line)
{
	static t_string_buffer	*buff;
	ssize_t					ret;
	char					temp_str[BUFFER_SIZE + 1];
	t_string_buffer			*relative;
	off_t					pos;

	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (buff == NULL)
	{
		buff = malloc(sizeof(t_string_buffer));
		if (buff == NULL)
			return (-1);
		buff->next = NULL;
		buff->depth = 0;
	}
	// write(1, "2", 1);
	relative = get_last(buff);
	// write(1, "a", 1);
	// pos = find_newline(relative->str);
	// write(1, "b", 1);
	ret = read(fd, temp_str, BUFFER_SIZE);
	// write(1, "c", 1);
	pos = find_newline(&temp_str[0]);
	// write(1, "d", 1);
	temp_str[ret] = 0;
	relative->str = temp_str;
	// write(1, "3", 1);
	while (ret > 0 && pos == -1)
	{
		relative->str = temp_str;
		// sleep(1);
//		test(temp_str);
		// write(1, "@", 1);
		ret = read(fd, temp_str, BUFFER_SIZE);
		if (ret == 0)
			break;
		relative->next = malloc(sizeof(t_string_buffer));
		if (relative->next == NULL)
			return (cleanup(&buff));
		// write(1, "#", 1);
		relative->next->depth = relative->depth + 1;
		// write(1, "&", 1);
		relative = relative->next;
		// write(1, "$", 1);
		relative->next = NULL;
		// write(1, "~", 1);
		temp_str[ret] = 0;
		pos = find_newline(&temp_str[0]);
	}
	// write(1, "4", 1);
	*line = combine_string(buff, relative->depth, pos);
	// write(1, "5", 1);
	if (ret != 0)
		ret = (ret < 0) ? -1 : 1;
	// write(1, "6", 1);
	return (ret);
}
