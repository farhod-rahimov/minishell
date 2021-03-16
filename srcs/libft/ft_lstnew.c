/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:40:48 by btammara          #+#    #+#             */
/*   Updated: 2020/11/10 10:13:47 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_el;

	if (!(new_el = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_el->content = content;
	new_el->next = 0;
	return (new_el);
}
