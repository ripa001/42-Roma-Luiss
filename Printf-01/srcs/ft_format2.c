/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 01:12:30 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/23 01:12:31 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../libft/libft.h"

char	*ft_hash(t_print *tab, char *a, char is_upper, int i)
{
	char	*b;
	char	*c;
	int		x;

	if (is_upper == 'X')
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

int	check_set(char c, char *set)
{
	int	k;

	k = 0;
	while (set[k])
	{
		if (c == set[k])
			return (1);
		k++;
	}
	return (0);
}

char	*ft_find_prc(t_print *tab, char *f, int *n)
{
	*n = 1;
	if (*f == '*')
	{
		tab->prc = va_arg(tab->args, int);
		f++;
		if (tab->prc < 0)
		{
			tab->prc = 0;
			tab->pnt = 0;
		}
	}
	else
	{
		while (ft_isdigit(*f))
		{
			tab->prc = (tab->prc * 10) + (*f - '0');
			f++;
		}
	}
	return (f);
}
