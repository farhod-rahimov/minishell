/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:38:44 by btammara          #+#    #+#             */
/*   Updated: 2020/11/10 11:32:50 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	strlen(const char *s)
{
	unsigned long int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char			*ret_ft(const char *haystack, const char *needle,
size_t a, size_t b)
{
	if (!needle[b])
		return ((char *)haystack + a);
	else if (!(needle[b + 1]) && strlen(haystack) == strlen(needle))
		return ((char *)haystack + a);
	return (NULL);
}

char			*strnstr_ft(const char *haystack,
const char *needle, size_t len)
{
	size_t	a;
	size_t	b;
	size_t	c;

	a = 0;
	b = 0;
	c = 0;
	while (haystack[a] != '\0' && a < len)
	{
		c = a;
		if (haystack[c] == needle[b])
		{
			while (haystack[c] != '\0' && needle[b] != '\0'
	&& c < len && haystack[c] == needle[b])
			{
				c++;
				b++;
			}
			if ((ret_ft(haystack, needle, a, b)))
				return (((ret_ft(haystack, needle, a, b))));
		}
		b = 0;
		a++;
	}
	return (NULL);
}

char			*ft_strnstr(const char *haystack,
const char *needle, size_t len)
{
	if (!(needle[0]))
		return ((char *)haystack);
	return (strnstr_ft(haystack, needle, len));
}
