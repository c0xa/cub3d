/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:53:24 by tblink            #+#    #+#             */
/*   Updated: 2020/11/03 20:14:31 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *pwd;

	pwd = *lst;
	while (pwd)
	{
		pwd = (*lst)->next;
		ft_lstdelone((*lst), del);
		*lst = pwd;
	}
}
