/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maintest_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 13:42:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/04/07 17:53:47 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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

void go_read(int fd)
{
	int result;
	char	*line;

	line = malloc(10);
	while ((result = get_next_line(fd, &line)) == 1)
	{
		if (line == NULL)
			write(1, "null k1rel", 10);
		write(1, "@#", 2);
		write(1, line, getlen(line));
		write(1, "#@\n", 3);
	}
	if (result == 0)
	{
		if (line == NULL)
			write(1, "null k2rel", 10);
		write(1, "@#", 2);
		write(1, line, getlen(line));
		write(1, "#@\n", 3);
		write(1, "\nEOF REACHED", 12);
	}
	// ER IS ALSNOG ERGENS EEN LEAK REEEEE
}

int	main(void)
{
	int		fd;
	// int		fd1;
	// int		fd2;
	int		result;
	char	*line;
	char	**test;
	char	c;
	int i = 0;

	line = malloc(256);
	result = 0;
	if (result == 0)
		result = -1;
	c = 1;
	if (c == 1)
		c = 'a';
	test = &line;
	// *test = "WWWWWWWWWWWWWWWWWW";
	// fd1 = open("test2.txt", O_RDONLY);
	// fd2 = open("test4.txt", O_RDONLY);
	#ifndef TYPING
	fd = open(FILENAME, O_RDONLY);
	#else
	fd = 0;
	#endif
	if (fd == 0)
		write(1, "remember, ^D to exit stdin\n", 27);
	while (i < 10)
	{
		fd = open(FILENAME, O_RDONLY);
		go_read(fd);
		close(fd);
		i++;
	}
	write(1, "karel", 5);
	// while(1);
	// result = get_next_line(fd, &line);
	// c = '0' + result;
	// write(1, &c, 1);
	// write(1, line, getlen(line));
	// write(1, "\n", 1);
	// result = get_next_line(fd, &line);
	// c = '0' + result;
	// write(1, &c, 1);
	// write(1, line, getlen(line));
	// get_next_line(fd, &line);
	// write(1, line, getlen(line));
	// write(1, "!!\n", 3);
	// get_next_line(fd1, &line);
	// write(1, line, getlen(line));
	// write(1, "<<\n", 3);
	// get_next_line(fd2, &line);
	// write(1, line, getlen(line));
	// write(1, ">>\n", 3);
	// get_next_line(fd1, &line);
	// write(1, line, getlen(line));
	// write(1, "^^\n", 3);
	// get_next_line(fd1, &line);
	// write(1, line, getlen(line));
	// write(1, "$$\n", 3);
	// get_next_line(fd, &line);
	// write(1, line, getlen(line));
	// write(1, "**\n", 3);
	// while ((result = get_next_line(fd, &line)) == 1)
	// {
	// 	if (line == NULL)
	// 		write(1, "null k1rel", 10);
	// 	write(1, "@#", 2);
	// 	write(1, line, getlen(line));
	// 	write(1, "#@\n", 3);
	// }
	// if (result == 0)
	// {
	// 	if (line == NULL)
	// 		write(1, "null k2rel", 10);
	// 	write(1, "@#", 2);
	// 	write(1, line, getlen(line));
	// 	write(1, "#@\n", 3);
	// 	write(1, "\nEOF REACHED", 12);
	// }
	// close(fd);
	// close(fd1);
	// close(fd2);
}