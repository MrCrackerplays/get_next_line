/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 17:22:45 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/06 16:49:31 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

off_t	find_newline(char *str)
{
	off_t	off;

	off = 0;
	while (str[off] != '\0')
	{
		if (str[off] == '\n')
			return (off);
		off++;
	}
	return (-1);
}
