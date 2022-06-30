/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_other3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini@student.42roma.it <mpatrini>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:41:38 by mpatrini@st       #+#    #+#             */
/*   Updated: 2022/03/03 14:41:38 by mpatrini@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sx(t_print *tab)
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
	ft_sprint_str(tab, a);
}

void	ft_sx_up(t_print *tab)
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
	ft_sprint_str(tab, a);
}

void	ft_sprint_str(t_print *tab, char *a)
{
	tab->tl += (int)ft_strlen(a);
	tab->str = ft_strjoin_free(tab->str, a);
}
