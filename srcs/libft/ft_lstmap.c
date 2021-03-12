/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:33:58 by btammara          #+#    #+#             */
/*   Updated: 2020/11/10 10:55:56 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		size;
	t_list	*temp;
	t_list	*b_temp;
	t_list	*b_list;

	if (lst == NULL || (temp = ft_lstnew(f(lst->content))) == NULL)
		return (NULL);
	size = ft_lstsize(lst);
	b_temp = temp;
	b_list = lst;
	while (--size)
	{
		lst = lst->next;
		temp->next = ft_lstnew(f(lst->content));
		if (temp->next == NULL)
		{
			lst = b_list;
			ft_lstclear(&b_temp, del);
			return (NULL);
		}
		temp = temp->next;
	}
	lst = b_list;
	return (b_temp);
}
