/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 22:20:18 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/19 22:20:18 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	free_all2(t_struct *data)
{
	free(data->ar_a);
	free(data->ar_b);
	free(data);
}

void	free_nbrs(char **nbrs)
{
	int	i;

	i = 0;
	while (nbrs[i])
	{
		free(nbrs[i]);
		i++;
	}
	free(nbrs);
}

int	ft_exit(char *str)
{
	ft_putstr_fd(str, 1);
	return (0);
}
