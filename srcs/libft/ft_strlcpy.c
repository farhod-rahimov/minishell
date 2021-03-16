/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:16:36 by btammara          #+#    #+#             */
/*   Updated: 2020/11/06 17:41:11 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		ostalos;
	const char	*src1;

	ostalos = dstsize;
	src1 = src;
	if (src == NULL)
		return (0);
	if (ostalos != 0)
	{
		while (--ostalos != 0)
		{
			if ((*dst++ = *src++) == '\0')
				break ;
		}
	}
	if (ostalos == 0)
	{
		if (dstsize != 0)
			*dst = '\0';
		while (*src++)
			;
	}
	return (src - src1 - 1);
}
