/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:31:50 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/01 15:04:45 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	check_row(char *s)
{
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*ft_get_buff(int i, char *buffer_line, char *buff, int fd)
{
	while (i > 0 && check_row(buffer_line) == 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == 0)
			break ;
		else if (i < 0)
			return (NULL);
		buffer_line = ft_strjoin_free(buffer_line, buff, i);
		if (ft_strlen_gnl(buffer_line) == 0)
		{
			free(buffer_line);
			free(buff);
			return (NULL);
		}
	}
	if (i < 0)
	{
		free(buffer_line);
		free(buff);
		return (NULL);
	}
	return (buffer_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer_line = NULL;
	char		*buff;
	char		*res;
	size_t		i;
	int			c;

	if (fd > 256 || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	c = 0;
	res = NULL;
	buff = malloc(BUFFER_SIZE + 1);
	buff[BUFFER_SIZE] = 0;
	i = 1;
	buffer_line = ft_get_buff(i, buffer_line, buff, fd);
	if (buffer_line == NULL)
	{
		free(buffer_line);
		free(buff);
		return (NULL);
	}
	c = ft_strchr_edit(buffer_line, '\n');
	res = ft_substr_edit(buffer_line, 0, c, 0);
	buffer_line = ft_substr_edit(buffer_line, c + 1, ft_strlen_gnl(buffer_line), 1);
	free(buff);
	return (res);
}
