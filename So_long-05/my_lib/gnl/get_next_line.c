/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:31:50 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 17:03:28 by dripanuc         ###   ########.fr       */
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

char	*ft_get_buff(int i, char *bl, char *buff, int fd)
{
	while (i > 0 && check_row(bl) == 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == 0)
			break ;
		else if (i < 0)
			return (NULL);
		bl = ft_strjoin_free(bl, buff, i);
		if (ft_strlen_gnl(bl) == 0)
		{
			free(bl);
			free(buff);
			return (NULL);
		}
	}
	if (i < 0)
	{
		free(bl);
		free(buff);
		return (NULL);
	}
	return (bl);
}

char	*get_next_line(int fd)
{
	static char	*bl = NULL;
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
	bl = ft_get_buff(i, bl, buff, fd);
	if (bl == NULL)
	{
		free(bl);
		free(buff);
		return (NULL);
	}
	c = ft_strchr_edit(bl, '\n');
	res = ft_substr_edit(bl, 0, c, 0);
	bl = ft_substr_edit(bl, c + 1, ft_strlen_gnl(bl), 1);
	free(buff);
	return (res);
}
