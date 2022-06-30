/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 00:32:53 by mpatrini          #+#    #+#             */
/*   Updated: 2022/02/05 19:25:00 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_u_wdt(t_print *tab, char *i, int c, int flag)
{
	char	*b;

	if (tab->wdt != 0)
	{
		if ((tab->wdt - c) > 0)
		{
			b = ft_memset(ft_calloc(tab->wdt, 1), flag, (size_t)tab->wdt - c);
			if (tab->dash == 1)
				i = ft_strjoin_free(i, b);
			else
				i = ft_strjoin_free(b, i);
		}
	}
	return (i);
}

char	*ft_u_prc(t_print *tab, char *i, unsigned int a)
{
	char	*b;

	if (tab->pnt == 1)
	{
		if (a == 0 && tab->prc == 0)
		{
			free(i);
			i = ft_calloc(1, 1);
		}
		if (tab->prc > (int)ft_strlen(i))
		{
			b = ft_memset(ft_calloc(tab->prc + 1, 1), 48, \
			tab->prc - ft_strlen(i));
			i = ft_strjoin_free(b, i);
		}
	}
	return (i);
}

void	ft_u(t_print *tab)
{
	unsigned int	a;
	char			*i;
	int				flag;
	int				c;

	a = va_arg(tab->args, unsigned int);
	i = ft_utoa(a);
	flag = 32;
	if (tab->is_zero == 1 && tab->dash == 0 && tab->pnt == 0)
		flag = 48;
	i = ft_u_prc(tab, i, a);
	c = ft_strlen(i);
	i = ft_u_wdt(tab, i, c, flag);
	ft_print_str(tab, i);
	free(i);
}

char	*ft_di_wdt(t_print *tab, char *i, int c, int flag)
{
	char	*b;

	if (tab->wdt != 0)
	{
		if ((tab->wdt - c) > 0 && flag == 32)
		{
			b = ft_memset(ft_calloc(tab->wdt, 1), flag, (size_t)tab->wdt - c);
			if (tab->dash == 1)
				i = ft_strjoin_free(ft_num_sign(tab, i), b);
			else
				i = ft_strjoin_free(b, ft_num_sign(tab, i));
		}
		else if ((tab->wdt - c) > 0 && flag == 48)
		{
			b = ft_memset(ft_calloc(tab->wdt, 1), flag, (size_t)tab->wdt - c);
			if (tab->dash == 1)
				i = ft_strjoin_free(ft_num_sign(tab, i), b);
			else
				i = ft_num_sign(tab, ft_strjoin_free(b, i));
		}
	}
	return (i);
}

void	ft_di(t_print *tab)
{
	int		a;
	char	*i;
	int		flag;
	int		c;

	flag = 32;
	a = va_arg(tab->args, int);
	i = ft_itoa(a);
	if (tab->is_zero == 1 && tab->dash == 0 && tab->pnt == 0)
		flag = 48;
	if (a < 0)
	{
		i = ft_substr_free(i, 1, ft_strlen(i) - 1);
		tab->is_neg = 1;
	}
	i = ft_di_prc(tab, i, a);
	c = ft_strlen(i);
	if (tab->is_neg == 1 || tab->sign == 1 || tab->sp == 1)
		c += 1;
	i = ft_di_wdt(tab, i, c, flag);
	if (tab->wdt == 0 || (tab->wdt - c) <= 0)
		i = ft_num_sign(tab, i);
	ft_print_str(tab, i);
	free(i);
}
