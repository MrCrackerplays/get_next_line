/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maintest.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 13:42:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/03/17 11:15:41 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"
#include "stdlib.h"
#include "unistd.h"
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

void spacing(char **str)
{
	int len;
	char *s;

	len = ft_strlen(*str);
	len = (len < 35 ? 35 - len : 0);
	s = malloc(1);
	*s = '\0';
	while (len > 0)
	{
		str_join(&s, " ", 0);
		len--;
	}
	str_join(str, s, 0);
}

int	main(void)
{
	int		fd;
	int		result;
	char	*line;
	char	**test;
	char	c;

	line = malloc(256);
	result = 0;
	if (result == 0)
		result = -1;
	c = 1;
	if (c == 1)
		c = 'a';
	test = &line;
	// *test = "WWWWWWWWWWWWWWWWWW";
	#ifndef TYPING
	fd = open(FILENAME, O_RDONLY);
	#else
	fd = 0;
	#endif
	if (fd == 0)
		write(1, "remember, ^D to exit stdin\n", 27);
	// result = get_next_line(fd, &line);
	// c = '0' + result;
	// write(1, &c, 1);
	// write(1, line, getlen(line));
	// write(1, "\n", 1);
	// result = get_next_line(fd, &line);
	// c = '0' + result;
	// write(1, &c, 1);
	// write(1, line, getlen(line));
	while ((result = get_next_line(fd, &line)) == 1)
	{
		write(1, "@#", 2);
		write(1, line, getlen(line));
		write(1, "#@\n", 3);
	}
	if (result == 0)
	{
		write(1, "@#", 2);
		write(1, line, getlen(line));
		write(1, "#@\n", 3);
		write(1, "\nEOF REACHED", 12);
	}
	close(fd);
}