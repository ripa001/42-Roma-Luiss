/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fun2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 04:31:28 by mpatrini          #+#    #+#             */
/*   Updated: 2022/02/05 19:24:17 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_c(t_print *tab)
{
	int		x;
	char	*b;

	x = va_arg(tab->args, int);
	if (tab->wdt != 0)
	{
		b = ft_calloc(tab->wdt, sizeof(char));
		b = (char *)ft_memset(b, 32, tab->wdt - 1);
		if (tab->dash == 1)
		{
			ft_putchar_fd(x, 1);
			ft_print_str(tab, b);
			free(b);
		}
		else
		{
			ft_print_str(tab, b);
			ft_putchar_fd(x, 1);
			free(b);
		}
	}
	else
		ft_putchar_fd(x, 1);
	tab->tl += 1;
	tab = ft_clear_tab(tab);
}

void	ft_print_str(t_print *tab, char *a)
{
	tab->tl += (int)ft_strlen(a);
	ft_putstr_fd(a, tab->fd);
}

void	ft_s(t_print *tab)
{	
	char	*a;
	char	*b;
	int		c;

	a = va_arg(tab->args, char *);
	if (a == NULL)
		a = "(null)";
	a = ft_substr(a, 0, ft_strlen(a));
	if (tab->pnt == 1)
		a = ft_substr_free(a, 0, tab->prc);
	c = ft_strlen(a);
	if (tab->wdt != 0)
	{
		if ((tab->wdt - c) > 0)
		{
			b = ft_memset(ft_calloc(tab->wdt, 1), 32, (size_t)tab->wdt - c);
			if (tab->dash == 1)
				a = ft_strjoin_free(a, b);
			else
				a = ft_strjoin_free(b, a);
		}
	}
	ft_print_str(tab, a);
	free(a);
}

void	ft_p(t_print *tab)
{
	char	*a;
	size_t	i;
	char	*b;
	char	*c;

	i = va_arg(tab->args, size_t);
	a = ft_hex_long_itoa(i, "0123456789abcdef");
	b = ft_memset(ft_calloc(2, 1), 48, 1);
	c = ft_memset(ft_calloc(2, 1), 120, 1);
	b = ft_strjoin_free(b, c);
	a = ft_strjoin_free(b, a);
	i = ft_strlen(a);
	if ((tab->wdt - (int)i) > 0)
	{
		b = ft_memset(ft_calloc(tab->wdt, 1), 32, (size_t)tab->wdt - i);
		if (tab->dash == 1)
			a = ft_strjoin_free(a, b);
		else
			a = ft_strjoin_free(b, a);
	}
	ft_print_str(tab, a);
	free(a);
}

char	*ft_hash(t_print *tab, char *a, int is_upper, int i)
{
	char	*b;
	char	*c;
	int		x;

	if (is_upper == 1)
		x = 88;
	else
		x = 120;
	if (tab->hash == 1 && i != 0)
	{
		b = ft_memset(ft_calloc(2, 1), 48, 1);
		c = ft_memset(ft_calloc(2, 1), x, 1);
		b = ft_strjoin_free(b, c);
		a = ft_strjoin_free(b, a);
	}
	return (a);
}
