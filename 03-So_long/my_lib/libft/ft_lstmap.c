/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:11:04 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/14 17:15:21 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*newlst;

	new = ft_lstnew(f(lst->content));
	if (!(new))
	{
		ft_lstclear(&lst, del);
		return (0);
	}
	newlst = new;
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!(new))
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&newlst, del);
			return (0);
		}
		lst = lst->next;
		ft_lstadd_back(&newlst, new);
	}
	return (newlst);
}
