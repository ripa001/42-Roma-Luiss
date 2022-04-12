/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:21:46 by ebassi            #+#    #+#             */
/*   Updated: 2022/02/11 16:47:00 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[257];

	if (fd < 0 || fd > 257 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = get_line(fd, save[fd]);
	line = get_res_line(save[fd]);
	save[fd] = mod_save(save[fd]);
	return (line);
}

char	*mod_save(char *save)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	res = malloc(sizeof(char) * ft_strlen_gnl(save) - i + 1);
	if (!res)
		return (NULL);
	i++;
	while (save[i])
		res[j++] = save[i++];
	res[j] = '\0';
	free(save);
	return (res);
}

char	*get_line(int fd, char *save)
{
	int		count;
	char	*buffer;

	count = 1;
	buffer = ft_calloc_gnl(1, BUFFER_SIZE + 1);
	if (!save)
		save = ft_calloc_gnl(1, 1);
	while (count > 0 && ft_strchr_gnl(save, '\n') == -1)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count <= 0)
			break ;
		buffer[count] = '\0';
		if (count < BUFFER_SIZE)
			count = 0;
		save = ft_strjoin_gnl(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_res_line(char *file)
{
	int		i;
	char	*line;

	i = 0;
	if (!file[i])
		return (NULL);
	while (file[i] && file[i] != '\n')
		i++;
	line = malloc (sizeof(char) * (i + 2));
	i = 0;
	while (file[i] && file[i] != '\n')
	{
		line[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
	{
		line[i] = file[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
