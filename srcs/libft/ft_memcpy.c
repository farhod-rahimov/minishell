/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:02:33 by btammara          #+#    #+#             */
/*   Updated: 2020/11/06 11:02:41 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*str1;
	const	char	*str2;
	size_t			i;

	str1 = (char *)dst;
	str2 = (const char *)src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (str1 == str2)
		return (dst);
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dst);
}
