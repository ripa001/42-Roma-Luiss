/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:57:13 by ebassi            #+#    #+#             */
/*   Updated: 2022/04/12 17:46:32 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *data)
{
	int	i;

	i = 0;
	if (data[0] == 'c' && data[1] == 'd' && data[2] == ' ' && data[3])
		return (&data[3]);
	return (0);
}

void	change_dir(t_tok *input_ln)
{
	char	*str;
	char	*home_path;

	str = 0;
	home_path = getenv("HOME");
	if (!ft_strncmp(input_ln->data, "cd", ft_strlen(input_ln->data)))
		chdir(home_path);
	else
	{
		// QUESTO E' SBAGLIATO

		str = get_path(input_ln->data);
		str = ft_strjoin("/", str);
		str = ft_strjoin(getcwd(NULL, 0), str);
		chdir(str);
	}
}