/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:32:24 by dripanuc          #+#    #+#             */
/*   Updated: 2022/12/03 18:32:25 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	utility_atof(const char *s, float *fact, float *rez)
{
	int		d;
	int		point_seen;

	d = 0;
	point_seen = 0;
	while (*s)
	{
		if (*s == '.' && s++)
		{
			point_seen = 1;
			continue ;
		}
		d = *s - '0';
		if (d >= 0 && d <= 9)
		{
			if (point_seen)
				*fact /= 10.0f;
			*rez = *rez * 10.0f + (float)d;
		}
		s++;
	}
}

float	ft_atof(const char *s)
{
	float	rez;
	float	fact;

	rez = 0;
	fact = 1;
	if (*s == '-' && s++)
		fact = -1;
	utility_atof(s, &fact, &rez);
	return (rez * fact);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign *= -1;
			str++;
			break ;
		}
		str++;
		break ;
	}
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - '0';
		str++;
	}
	return (sign * num);
}
