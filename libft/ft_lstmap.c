/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:47:44 by tblink            #+#    #+#             */
/*   Updated: 2020/11/04 19:10:14 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *))
{
	t_list *pwd;
	t_list *element;

	if (!lst || !(pwd = ft_lstnew(f(lst->content))))
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		if (!(element = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&pwd, del);
			return (NULL);
		}
		ft_lstadd_back(&pwd, element);
		lst = lst->next;
	}
	return (pwd);
}
