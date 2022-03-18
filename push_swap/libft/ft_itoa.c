/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:57:21 by mabasset          #+#    #+#             */
/*   Updated: 2022/01/13 17:37:55 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strrev(char *str)
{
	int		index;
	int		len;
	char	temp;

	index = 0;
	len = 0;
	while (str[len] != '\0')
		len++;
	len -= 1;
	while (index < len)
	{
		temp = str[len];
		str[len] = str[index];
		str[index] = temp;
		len--;
		index++;
	}
}

void	ft_re_strlen(long int nbr, int *len)
{
	if (nbr >= 10)
		ft_re_strlen(nbr / 10, len);
	*len += 1;
}

void	ft_recursive(long int nbr, char *str)
{
	if (nbr >= 10)
		ft_recursive(nbr / 10, str + 1);
	*str = nbr % 10 + '0';
}

char	*ft_putnbr(long int nbr, int flag)
{
	char	*str;
	int		len;

	len = 0;
	ft_re_strlen(nbr, &len);
	str = (char *) malloc (sizeof(char) * len + flag);
	if (str == NULL)
		return (NULL);
	if (flag == 2)
		str[len] = '-';
	str[len + flag - 1] = '\0';
	ft_recursive(nbr, str);
	return (&str[0]);
}

char	*ft_itoa(int nbr)
{
	long int	nb;
	char		*str;
	int			flag;

	flag = 1;
	nb = nbr;
	if (nb < 0)
	{
		nb = nb * -1;
		flag = 2;
	}
	str = ft_putnbr(nb, flag);
	ft_strrev(str);
	return (str);
}
