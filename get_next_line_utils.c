/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 11:12:03 by pdruart       #+#    #+#                 */
/*   Updated: 2020/12/12 17:44:13 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "unistd.h"
#include "stdlib.h"

int		ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	str_join(char **original, char *addition)
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
