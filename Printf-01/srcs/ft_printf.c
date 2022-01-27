/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:32:23 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/23 01:18:26 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../libft/libft.h"

char	*ft_wdt_x(t_print *tab, char *a, int flag)
{
	char	*b;
	int		i;

	i = ft_strlen(a);
	if ((tab->wdt - (int)i) > 0)
	{
		b = ft_memset(ft_calloc(tab->wdt, 1), flag, (size_t)tab->wdt - i);
		if (tab->dash == 1)
			a = ft_strjoin_free(a, b);
		else
			a = ft_strjoin_free(b, a);
	}
	return (a);
}

void	ft_x(t_print *tab, char c)
{
	char	*a;
	size_t	i;
	int		flag;

	flag = 32;
	i = va_arg(tab->args, size_t);
	if (c == 'x')
		a = ft_hex_itoa(i, "0123456789abcdef");
	else
		a = ft_hex_itoa(i, "0123456789ABCDEF");
	if (tab->is_zero == 1 && tab->dash == 0 && tab->pnt == 0)
		flag = 48;
	a = ft_prc_x(tab, a, i);
	a = ft_hash(tab, a, c, i);
	a = ft_wdt_x(tab, a, flag);
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

int	ft_printf(const char *s, ...)
{
	int			i;
	t_print		*params;

	params = malloc(sizeof(t_print));
	ft_initialise_tab(params);
	va_start(params->args, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			ft_reset_tab(params);
			check_format((char *)&s[i], params);
			i++;
			while (!(check_set(s[i], "cspdiuxX%")))
				i++;
		}
		else
			params->tl += write(1, &s[i], 1);
		i++;
	}
	va_end(params->args);
	free(params);
	return (params->tl);
}

//int main()
//{
//	int				i = -6789;
//	unsigned int	ui = 4294967295;
//	//char 			s[] = "stringa";
//	int num;
//	int num2;
//	//printf("ft_printf :");
//	//printf("\t%d\n\n", 
//	ft_printf(" %-1s %-2s \n", "", "-");
//	//fflush(stdout);
//	//printf("    printf :");
//	//printf("\t%d\n", 
//	printf(" %-1s %-2s \n", "", "-");
//	return (0);
//}