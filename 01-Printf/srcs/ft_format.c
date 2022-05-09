/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 00:44:34 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/23 01:15:30 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../libft/libft.h"

char	*ft_find_wdt(t_print *tab, char *f)
{
	if (*f == '*')
	{
		tab->wdt = va_arg(tab->args, int);
		if (tab->wdt < 0)
		{
			tab->wdt *= -1;
			tab->dash = 1;
		}
	}
	else
	{
		while (ft_isdigit(*f))
		{
			tab->wdt = (tab->wdt * 10) + (*f - '0');
			f++;
		}
		f--;
	}
	return (f--);
}

void	check_type(t_print *params, char *c)
{
	if (*c == 'c')
		ft_c(params);
	else if (*c == 'd' || *c == 'i')
		ft_di(params);
	else if (*c == 'x' || *c == 'X')
		ft_x(params, *c);
	else if (*c == 'u')
		ft_u(params);
	else if (*c == 'p')
		ft_p(params);
	else if (*c == 's')
		ft_s(params);
	c++;
}

void	get_flag(t_print *params, char *c)
{
	if (*c == '0' && params->dash != 1)
		params->is_zero = 1;
	else if (*c == '+')
		params->sign = 1;
	else if (*c == '#')
		params->hash = 1;
	else if (*c == ' ')
		params->sp = 1;
}

char	*check_flag(t_print *params, char *c, int *n)
{
	if (*c == '.')
	{
		params->pnt = 1;
		c = ft_find_prc(params, ++c, n);
		return (c);
	}
	else if (*c == '0' && params->dash != 1)
		params->is_zero = 1;
	else if (*c == '+')
		params->sign = 1;
	else if (*c == '#')
		params->hash = 1;
	else if (*c == ' ')
		params->sp = 1;
	else if (*c == '-')
		params->dash = 1;
	else if (*c == '%')
	{
		params->tl += write(1, "%", 1);
		*n = -1;
		return (c++);
	}
	else if (ft_isdigit(*c) || *c == '*')
		c = ft_find_wdt(params, c);
	return (c);
}

void	check_format(char *c, t_print *params)
{
	int	y;
	int	*n;

	y = 0;
	n = &y;
	c++;
	while (!(check_set(*c, "cspdiuxX")))
	{
		*n = 0;
		c = check_flag(params, c, n);
		if (*n == 1)
			continue ;
		else if (*n == -1)
			return ;
		c++;
	}
	check_type(params, c);
}
