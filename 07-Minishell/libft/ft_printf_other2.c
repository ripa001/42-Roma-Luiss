/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_other2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini@student.42roma.it <mpatrini>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:41:24 by mpatrini@st       #+#    #+#             */
/*   Updated: 2022/03/03 14:41:24 by mpatrini@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_su(t_print *tab)
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
	ft_sprint_str(tab, i);
}

void	ft_sdi(t_print *tab)
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
	ft_sprint_str(tab, i);
}

void	ft_sc(t_print *tab)
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
			ft_add_char(tab, x);
			ft_sprint_str(tab, b);
			free(b);
		}
		else
		{
			ft_sprint_str(tab, b);
			ft_add_char(tab, x);
			free(b);
		}
	}
	else
		ft_putchar_fd(x, 1);
	tab->tl += 1;
	tab = ft_clear_tab(tab);
}

void	ft_ss(t_print *tab)
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
	ft_sprint_str(tab, a);
}

void	ft_sp(t_print *tab)
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
	ft_sprint_str(tab, a);
}
