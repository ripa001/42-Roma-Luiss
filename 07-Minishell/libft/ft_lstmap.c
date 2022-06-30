/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 06:57:38 by mpatrini          #+#    #+#             */
/*   Updated: 2022/01/12 07:29:21 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*fi;
	t_list	*n;

	if (!f || !del)
		return (NULL);
	fi = NULL;
	while (lst)
	{
		n = ft_lstnew((*f)(lst->content));
		if (!n)
		{
			while (fi)
			{
				n = fi->next;
				(*del)(fi->content);
				free(fi);
				fi = n;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&fi, n);
		lst = lst->next;
	}
	return (fi);
}
