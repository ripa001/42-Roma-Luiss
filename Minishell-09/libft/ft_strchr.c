/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:28:15 by dripanuc          #+#    #+#             */
/*   Updated: 2022/04/04 18:42:16 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (*str != (unsigned char)c)
	{
		if (*str == 0)
			return (0);
		str++;
	}
	return ((char *)str);
}

int	ft_index_strchr(const char *s, int c)
{
	int				i;

	i = -1;
	while (s[++i] != c)
		if (s[i] == 0)
			return (i);
	return (i);
}