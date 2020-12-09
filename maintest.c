/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maintest.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 13:42:34 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/09 16:19:40 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"
#include "stdlib.h"
#ifndef FILENAME
# define FILENAME "test.txt"
#endif

int	getlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	main(void)
{
	int		fd;
	// int		result;
	char	*line;
	char	**test;

	line = malloc(256);
	test = &line;
	*test = "WWWWWWWWWWWWWWWWWW";
	#ifndef TYPING
	fd = open(FILENAME, O_RDONLY);
	#else
	fd = 0;
	#endif
	if (fd == 0)
		write(1, "remember, ^D to exit stdin\n", 27);
	write(1, "1", 1);
	get_next_line(fd, &line);
	write(1, "ARARA", 5);
	write(1, line, getlen(line));
	// while ((result = get_next_line(fd, &line)) == 1)
	// {
	// 	write(1, "@#", 2);
	// 	write(1, line, getlen(line));
	// 	write(1, "#@", 2);
	// }
	// if (result == 0)
	// 	write(1, line, getlen(line));
	close(fd);
}
