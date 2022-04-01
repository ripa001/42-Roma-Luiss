/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:17:40 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/21 18:18:10 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *s_n)
{
	s_n--;
	while (*++s_n)
		if (!ft_isdigit(*s_n))
			return (0);
	return (1);
}
