/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 23:06:20 by mpatrini          #+#    #+#             */
/*   Updated: 2022/02/05 19:24:46 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print	*ft_initialise_tab(int fd, t_print *tab)
{
	if (fd == -100)
		tab->fd = 1;
	else
		tab->fd = fd;
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
	return (tab);
}

t_print	*ft_clear_tab(t_print *tab)
{
	tab->wdt = 0;
	tab->prc = 0;
	tab->zero = 0;
	tab->pnt = 0;
	tab->sign = 0;
	tab->is_zero = 0;
	tab->dash = 0;
	tab->perc = 0;
	tab->sp = 0;
	tab->hash = 0;
	tab->is_neg = 0;
	return (tab);
}

int	ft_itoa_len(unsigned int n)
{
	int				len;
	unsigned int	tmp;

	len = 0;
	tmp = n;
	if (n == 0)
		len = 1;
	else
	{
		while (tmp)
		{
			tmp /= 10;
			len++;
		}
	}
	return (len);
}

char	*ft_utoa(unsigned int n)
{
	int				len;
	char			*str;

	len = ft_itoa_len(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len] = 0;
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	while (n)
	{
		str[--len] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}

char	*ft_num_sign(t_print *tab, char *i)
{
	if (tab->is_neg == 1)
		i = ft_strjoin_free(ft_memset(ft_calloc(2, 1), 45, 1), i);
	else if (tab->sign == 1)
		i = ft_strjoin_free(ft_memset(ft_calloc(2, 1), 43, 1), i);
	else if (tab->sign == 0 && tab->sp == 1)
		i = ft_strjoin_free(ft_memset(ft_calloc(2, 1), 32, 1), i);
	return (i);
}
