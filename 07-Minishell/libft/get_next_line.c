/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:55:19 by mpatrini          #+#    #+#             */
/*   Updated: 2022/02/05 19:18:20 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(int fd, char *line)
{
	char	*buffer;
	int		i;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	i = 1;
	while (!ft_strchr(line, '\n') && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[i] = 0;
		if (!line)
			line = buffer;
		else
			line = ft_strjoin_get(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*ft_ret_line(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	ret = (char *)malloc(i + 2);
	if (!ret)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		ret[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		ret[i] = '\n';
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_modify_line(char *line)
{
	int		i;
	char	*new;
	int		in;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	new = (char *)malloc(ft_strlen_get(line) - i + 1);
	if (!new)
		return (NULL);
	i += 1;
	in = 0;
	while (line[i])
		new[in++] = line[i++];
	new[in] = 0;
	free(line);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*line[257];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	if (!line[fd])
		line[fd] = ft_strdup_get("");
	line[fd] = ft_read(fd, line[fd]);
	if (line[fd] == NULL)
		return (NULL);
	ret = ft_ret_line(line[fd]);
	line[fd] = ft_modify_line(line[fd]);
	return (ret);
}
