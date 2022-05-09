/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:31:50 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/27 00:18:50 by dripanuc         ###   ########.fr       */
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

char	*ft_get_buff(int i, char *bline, char *buff, int fd)
{
	while (i > 0 && check_row(bline) == 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == 0)
			break ;
		else if (i < 0)
			return (NULL);
		bline = ft_strjoin_free(bline, buff, i);
		if (ft_strlen(bline) == 0)
		{
			free(bline);
			free(buff);
			return (NULL);
		}
	}
	if (i < 0)
	{
		free(bline);
		free(buff);
		return (NULL);
	}
	return (bline);
}

char	*get_next_line(int fd)
{
	static char	*bline[257];
	char		*buff;
	char		*res;
	size_t		i;
	int			c;

	if (fd > 257 || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	c = 0;
	res = NULL;
	buff = malloc(BUFFER_SIZE + 1);
	buff[BUFFER_SIZE] = 0;
	i = 1;
	bline[fd] = ft_get_buff(i, bline[fd], buff, fd);
	if (bline[fd] == NULL)
	{
		free(bline[fd]);
		free(buff);
		return (NULL);
	}
	c = ft_strchr(bline[fd], '\n');
	res = ft_substr(bline[fd], 0, c, 0);
	bline[fd] = ft_substr(bline[fd], c + 1, ft_strlen(bline[fd]), 1);
	free(buff);
	return (res);
}
