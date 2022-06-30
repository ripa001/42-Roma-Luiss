/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_other.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini@student.42roma.it <mpatrini>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:38:28 by mpatrini@st       #+#    #+#             */
/*   Updated: 2022/03/20 15:47:33 by mpatrini@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print	*ft_initialise_stab(t_print *tab)
{
	tab->wdt = 0;
	tab->prc = 0;
	tab->zero = 0;
	tab->pnt = 0;
	tab->sign = 0;
	tab->tl = 0;
	tab->is_zero = 0;
	tab->dash = 0;
	tab->perc = 0;
	tab->sp = 0;
	tab->hash = 0;
	tab->is_neg = 0;
	tab->str = ft_calloc(2, 1);
	return (tab);
}

int	ft_sprint_char(t_print *tab, const char *f, int i)
{
	if (f[i] == 'c')
		ft_sc(tab);
	else if (f[i] == 's')
		ft_ss(tab);
	else if (f[i] == 'd' || f[i] == 'i')
		ft_sdi(tab);
	else if (f[i] == 'u')
		ft_su(tab);
	else if (f[i] == 'p')
		ft_sp(tab);
	else if (f[i] == 'x')
		ft_sx(tab);
	else if (f[i] == 'X')
		ft_sx_up(tab);
	else if (f[i] == '%')
	{
		ft_add_char(tab, '%');
		tab->tl += 1;
	}
	tab = ft_clear_tab(tab);
	return (i);
}

void	ft_add_char(t_print *tab, char c)
{
	char	*ret;

	ret = ft_memset(ft_calloc(2, 1), c, 1);
	tab->str = ft_strjoin_free(tab->str, ret);
}

int	ft_printfd(int fd, const char *format, ...)
{
	int		i;
	int		ret;
	t_print	*tab;

	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (0);
	ft_initialise_tab(fd, tab);
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
			ret += write(fd, &format[i], 1);
	}
	va_end(tab->args);
	ret += tab->tl;
	free (tab);
	return (ret);
}

char	*ft_sprintf(const char *format, ...)
{
	int		i;
	char	*ret;
	t_print	*tab;

	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (0);
	ft_initialise_stab(tab);
	va_start(tab->args, format);
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i = ft_format(tab, format, i);
			i = ft_sprint_char(tab, format, i);
		}
		else
			ft_add_char(tab, format[i]);
	}
	va_end(tab->args);
	ret = tab->str;
	free (tab);
	return (ret);
}
