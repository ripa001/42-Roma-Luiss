/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:15:58 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/20 16:51:20 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strcpy2(char *save, char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] != '\0')
	{
		save[j] = str[i + j];
		j++;
	}
	str[i] = '\0';
	save[j] = '\0';
}

char	*ft_save(char *str)
{
	char	*save;
	int		i;
	int		j;

	i = 0;
	if (ft_strchr(str, '\n') == 0)
		return (NULL);
	while (str[i] != '\n')
		i++;
	i += 1;
	j = i;
	while (str[j] != '\0')
		j++;
	if (j == i)
		return (NULL);
	save = (char *) malloc (sizeof(char) * (j + 1));
	if (save == NULL)
		return (NULL);
	ft_strcpy2(save, str, i);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*str;
	static char	*save[257];
	int			bytes;

	str = save[fd];
	bytes = 1;
	if (fd < 0 || fd > 256)
		return (NULL);
	buffer = (char *) malloc (sizeof(char) * 2);
	while (ft_strchr(str, '\n') == 0 && bytes > 0)
	{
		bytes = read(fd, buffer, 1);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		if (bytes < 1)
			bytes = 0;
		str = ft_strjoin(str, buffer);
	}
	free (buffer);
	save[fd] = ft_save(str);
	return (str);
}
