/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 09:44:06 by btammara          #+#    #+#             */
/*   Updated: 2020/11/06 17:37:02 by btammara         ###   ########.fr       */
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

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned	int	i;
	char			*p;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= strlen(s) || len == 0)
	{
		if ((p = (char *)malloc(1 * sizeof(char))))
			p[0] = '\0';
		return (p);
	}
	if ((p = (char *)malloc((len + 1) * sizeof(char))))
	{
		while (i < len && s[start] != '\0')
			p[i++] = s[start++];
		p[i] = '\0';
		return (p);
	}
	return (NULL);
}
