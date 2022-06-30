/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fun3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 04:31:28 by mpatrini          #+#    #+#             */
/*   Updated: 2022/02/05 19:24:13 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_x(t_print *tab)
{
	char	*a;
	size_t	i;
	char	*b;
	int		flag;

	flag = 32;
	i = va_arg(tab->args, size_t);
	a = ft_hex_itoa(i, "0123456789abcdef");
	if (tab->is_zero == 1 && tab->dash == 0 && tab->pnt == 0)
		flag = 48;
	a = ft_prc_x(tab, a, i);
	a = ft_hash(tab, a, 0, i);
	i = ft_strlen(a);
	if ((tab->wdt - (int)i) > 0)
	{
		b = ft_memset(ft_calloc(tab->wdt, 1), flag, (size_t)tab->wdt - i);
		if (tab->dash == 1)
			a = ft_strjoin_free(a, b);
		else
			a = ft_strjoin_free(b, a);
	}
	ft_print_str(tab, a);
	free(a);
}

void	ft_x_up(t_print *tab)
{
	char	*a;
	size_t	i;
	char	*b;
	int		flag;

	flag = 32;
	i = va_arg(tab->args, size_t);
	a = ft_hex_itoa(i, "0123456789ABCDEF");
	if (tab->is_zero == 1 && tab->dash == 0 && tab->pnt == 0)
		flag = 48;
	a = ft_prc_x(tab, a, i);
	a = ft_hash(tab, a, 1, i);
	i = ft_strlen(a);
	if ((tab->wdt - (int)i) > 0)
	{
		b = ft_memset(ft_calloc(tab->wdt, 1), flag, (size_t)tab->wdt - i);
		if (tab->dash == 1)
			a = ft_strjoin_free(a, b);
		else
			a = ft_strjoin_free(b, a);
	}
	ft_print_str(tab, a);
	free(a);
}

char	*ft_prc_x(t_print *tab, char *a, int i)
{
	char	*b;

	if (tab->pnt == 1)
	{
		if (i == 0 && tab->prc == 0)
		{
			free(a);
			a = ft_calloc(1, 1);
		}
		if (tab->prc > (int)ft_strlen(a))
		{
			b = ft_memset(ft_calloc(tab->prc + 1, 1), \
			48, tab->prc - ft_strlen(a));
			a = ft_strjoin_free(b, a);
		}
	}
	return (a);
}

char	*ft_di_prc(t_print *tab, char *i, int a)
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
