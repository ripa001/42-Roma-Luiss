/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:34:01 by mabasset          #+#    #+#             */
/*   Updated: 2022/01/18 18:36:50 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc (sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

/*#include <stdlib.h>
#include <unistd.h>

void	ft_print_result(char const *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

int		main(int argc, const char *argv[])
{
	char	s1[] = "tripouille";
	char	s2[] = "42";
	char	*strjoin;
	int		arg;

	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		if (!(strjoin = ft_strjoin(s1, s2)))
			ft_print_result("NULL");
		else
			ft_print_result(strjoin);
		if (strjoin == s1 || strjoin == s2)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 2)
	{
		s1[0] = '\0';
		if (!(strjoin = ft_strjoin(s1, s2)))
			ft_print_result("NULL");
		else
			ft_print_result(strjoin);
		if (strjoin == s1 || strjoin == s2)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 3)
	{
		s2[0] = '\0';
		if (!(strjoin = ft_strjoin(s1, s2)))
			ft_print_result("NULL");
		else
			ft_print_result(strjoin);
		if (strjoin == s1 || strjoin == s2)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 4)
	{
		s1[0] = '\0';
		s2[0] = '\0';
		if (!(strjoin = ft_strjoin(s1, s2)))
			ft_print_result("NULL");
		else
			ft_print_result(strjoin);
		if (strjoin == s1 || strjoin == s2)
			ft_print_result("\nA new string was not returned");
	}
	return (0);
}*/
