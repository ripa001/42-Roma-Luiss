/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:08:24 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/17 11:34:45 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*lst_new;

	lst_new = *lst;
	while (lst_new)
	{
		tmp = lst_new->next;
		ft_lstdelone(lst_new, del);
		lst_new = tmp;
	}
	*lst = NULL;
}
