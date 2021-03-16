/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove_MAIN.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:33:08 by btammara          #+#    #+#             */
/*   Updated: 2020/11/06 10:53:29 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = (char*)dst;
	str2 = (char*)src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (str1 <= str2 || str1 >= (str2 + len))
	{
		while (i < len)
		{
			str1[i] = str2[i];
			i++;
		}
	}
	else
	{
		while (len--)
			str1[len] = str2[len];
	}
	return (dst);
}
