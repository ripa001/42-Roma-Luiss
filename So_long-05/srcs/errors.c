/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:00:15 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 17:00:17 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	error(char *message)
{
	printf("\033[0;31m" " Error\n    %s\n" "\033[0m", message);
	return (0);
}

void	*null_error(char *message)
{
	printf("\033[0;31m" " Error\n	%s\n" "\033[0m", message);
	return (0);
}

void	print_warning(char *message)
{
	printf("\033[0;33m" " Warning\n %s\n" "\033[0m", message);
}
