/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 07:57:01 by btammara          #+#    #+#             */
/*   Updated: 2020/11/10 10:47:17 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_last;

	if (new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			lst_last = ft_lstlast(*lst);
			lst_last->next = new;
			new->next = NULL;
		}
	}
}
