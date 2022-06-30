/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:17:10 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/29 20:00:07 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_folder_size(char *dir)
{
	int				i;
	DIR				*folder;
	struct dirent	*entry;

	folder = opendir(dir);
	i = 0;
	while (1)
	{
		entry = readdir(folder);
		if (entry == NULL)
			break ;
		i++;
	}
	closedir(folder);
	return (i);
}

char	**ft_find_files3(char *dir, char *srch, int i)
{
	DIR				*folder;
	struct dirent	*entry;
	char			**files;

	folder = opendir(dir);
	if (folder == NULL)
	{
		ft_putendl_fd("Unable to read directory", 2);
		closedir(folder);
		exit(1);
	}
	files = malloc(sizeof(char *) * ft_folder_size(dir) + 2);
	while (1)
	{
		entry = readdir(folder);
		if (entry == NULL)
			break ;
		if (!ft_strncmp(srch, entry->d_name, ft_strlen(srch)))
			files[++i] = ft_strdup(entry->d_name);
	}
	files[++i] = 0;
	closedir(folder);
	return (files);
}

char	**ft_find_files(char *dir, int i)
{
	DIR				*folder;
	struct dirent	*entry;
	char			**files;

	folder = opendir(dir);
	if (folder == NULL)
	{
		ft_putendl_fd("Unable to read directory", 2);
		closedir(folder);
		exit(1);
	}
	files = malloc(sizeof(char *) * ft_folder_size(dir) + 3);
	files[0] = "prova";
	while (1)
	{
		entry = readdir(folder);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.')
			files[++i] = ft_strdup(entry->d_name);
	}
	files[++i] = 0;
	closedir(folder);
	return (files);
}

char	**ft_findwild_multi3(char *str, char *dir)
{
	char			**files;
	char			*sub_file;

	if (str[0] == '*')
		files = ft_find_files(dir, -1);
	else
	{
		sub_file = ft_substr(str, 0, ft_strchr(str, '*') - str);
		files = ft_find_files3(dir, sub_file, -1);
		free(sub_file);
	}
	return (files);
}

char	*ft_expand_wild(char *ret)
{
	char	**wild;
	char	*ret2;
	int		i;
	char	*dir;

	wild = ft_split(ret, 32);
	free(ret);
	dir = getcwd(NULL, 0);
	i = 0;
	while (wild[i])
	{
		if (ft_strchr(wild[i], '*'))
			wild[i] = ft_findwild_multi(wild[i], dir);
		else if (ft_strchr(wild[i], '*') != NULL && \
			ft_strchr(wild[i], '/') != NULL)
			ft_putendl_fd("Wildcards works only in current dir", STDERR);
		i++;
	}
	i = 0;
	ret2 = ft_rev_split(wild);
	free(dir);
	ft_free_matrix(wild);
	return (ret2);
}
