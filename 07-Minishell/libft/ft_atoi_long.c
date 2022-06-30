/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini@student.42roma.it <mpatrini>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 03:27:17 by mpatrini@st       #+#    #+#             */
/*   Updated: 2022/02/21 03:35:20 by mpatrini@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi_long(const char *str)
{
	int			i;
	int			s;
	long long	res;

	i = 0;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	s = 1;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			s *= -1;
		i += 1;
	}
	if (str[i] == 45 || str[i] == 43)
		return (0);
	if (s == 0)
		return (0);
	while (str[i] == 45 || str[i] == 43)
		i++;
	while (str[i] > 47 && str[i] < 58)
		res = (res * 10) + (str[i++] - 48);
	return (res * s);
}
