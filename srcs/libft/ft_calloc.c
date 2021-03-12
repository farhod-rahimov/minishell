/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 08:01:23 by btammara          #+#    #+#             */
/*   Updated: 2020/11/06 11:15:18 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			i;
	size_t			vsego;

	i = 0;
	vsego = count * size;
	if ((p = (unsigned char *)malloc(count * size)))
	{
		while (vsego--)
			p[i++] = 0;
		return ((void *)p);
	}
	return (NULL);
}
