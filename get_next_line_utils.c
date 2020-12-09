/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 17:22:45 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/09 17:05:00 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdlib.h"

off_t			find_newline(char *str)
{
	off_t	off;

	if (str == NULL)
		return (-1);
	off = 0;
	while (str[off] != '\0')
	{
		if (str[off] == '\n')
			return (off);
		off++;
	}
	return (-1);
}

t_string_buffer	*get_last(t_string_buffer *buff)
{
	if (buff == NULL)
		return (NULL);
	while (buff->next != NULL)
		buff = buff->next;
	return (buff);
}

int				cleanup(t_string_buffer **buff)
{
	if (buff == NULL)
		return (-1);
	if ((*buff)->next != NULL)
		cleanup(&((*buff)->next));
	// free((*buff)->str);
	free(*buff);
	*buff = NULL;
	return (-1);
}

void			clean_till_depth(t_string_buffer *buff, size_t dpt, off_t pos)
{
	t_string_buffer *temp;

	if (buff == NULL)
		return ;
	write(1, "!", 1);
	while (buff->depth != dpt)
	{
	write(1, "@", 1);
		temp = buff->next;
		// free(buff->str);
		free(buff);
		buff = temp;
	write(1, "#", 1);
	}
	write(1, "$", 1);
	if (pos == -1)
	{
		// free(buff->str);
		free(buff);
	}
	write(1, "^", 1);
}
int	getlenni(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}
char			*combine_string(t_string_buffer *buff, size_t dpt, off_t pos)
{
	char			*str;
	t_string_buffer	*temp;
	size_t			len;
	size_t			i;

	if (buff == NULL || buff->depth > dpt)
		return (NULL);
	i = 0;
	temp = buff;
	write(1, "q", 1);
	len = ((dpt - temp->depth) * BUFFER_SIZE + (pos == -1 ? BUFFER_SIZE : pos));
	write(1, "w", 1);
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	write(1, "z", 1);
	while (i < len)
	{
		write(1, "y", 1);
		if (temp->str == NULL)
			write(1, "*", 1);
		write(1, "\n", 1);
		write(1, str, getlenni(str));
		sleep(1);
		str[i] = temp->str[i % BUFFER_SIZE];
		write(1, "x", 1);
		i++;
		if (i % BUFFER_SIZE == 0)
			temp = temp->next;
	}
	write(1, "e", 1);
	clean_till_depth(buff, dpt, pos);
	write(1, "r", 1);
	return (str);
}
