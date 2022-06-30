/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:04:08 by mpatrini          #+#    #+#             */
/*   Updated: 2022/02/05 19:24:09 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_prc(t_print *tab, const char *f, int i)
{
	if (f[i + 1] == '*')
	{
		tab->prc = va_arg(tab->args, int);
		i++;
		if (tab->prc < 0)
		{
			tab->prc = 0;
			tab->pnt = 0;
		}
	}
	else
	{
		while (ft_isdigit(f[i + 1]))
		{
			tab->prc = (tab->prc * 10) + (f[i + 1] - 48);
			i++;
		}
	}
	return (i);
}

int	ft_find_wdt(t_print *tab, const char *f, int i)
{
	if (f[i] == '*')
	{
		tab->wdt = va_arg(tab->args, int);
		if (tab->wdt < 0)
		{
			tab->wdt *= -1;
			tab->dash = 1;
		}
	}
	else
		tab->wdt = (tab->wdt * 10) + (f[i] - 48);
	return (i);
}

int	ft_format(t_print *tab, const char *f, int topata)
{
	while (ft_strchr("udcspixX%", f[++topata]) == NULL)
	{
		if (f[topata] == '-')
			tab->dash = 1;
		else if (f[topata] == '.')
		{
			tab->pnt = 1;
			topata = ft_find_prc(tab, f, topata);
		}
		else if (f[topata] == '0' && ft_isdigit(f[topata - 1]) == 0)
			tab->is_zero = 1;
		else if (f[topata] == '#')
			tab->hash = 1;
		else if (f[topata] == ' ')
			tab->sp = 1;
		else if (f[topata] == '+')
			tab->sign = 1;
		else if (ft_isdigit(f[topata]) || f[topata] == '*')
			topata = ft_find_wdt(tab, f, topata);
	}
	return (topata);
}

int	ft_print_char(t_print *tab, const char *f, int i)
{
	if (f[i] == 'c')
		ft_c(tab);
	else if (f[i] == 's')
		ft_s(tab);
	else if (f[i] == 'd' || f[i] == 'i')
		ft_di(tab);
	else if (f[i] == 'u')
		ft_u(tab);
	else if (f[i] == 'p')
		ft_p(tab);
	else if (f[i] == 'x')
		ft_x(tab);
	else if (f[i] == 'X')
		ft_x_up(tab);
	else if (f[i] == '%')
	{
		write(tab->fd, "%", 1);
		tab->tl += 1;
	}
	tab = ft_clear_tab(tab);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		ret;
	t_print	*tab;

	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (0);
	ft_initialise_tab(-100, tab);
	va_start(tab->args, format);
	i = -1;
	ret = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i = ft_format(tab, format, i);
			i = ft_print_char(tab, format, i);
		}
		else
			ret += write(1, &format[i], 1);
	}
	va_end(tab->args);
	ret += tab->tl;
	free (tab);
	return (ret);
}
