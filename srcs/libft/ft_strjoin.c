/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:38:10 by btammara          #+#    #+#             */
/*   Updated: 2020/11/06 17:33:28 by btammara         ###   ########.fr       */
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

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*p;

	if (s1 == NULL)
		return (NULL);
	len = strlen(s1) + strlen(s2);
	i = 0;
	if ((p = (char *)malloc((len + 1) * sizeof(char))))
	{
		while (s1[i] != '\0')
		{
			p[i] = s1[i];
			i++;
		}
		len = i;
		i = 0;
		while (s2[i] != '\0')
			p[len++] = s2[i++];
		p[len] = '\0';
		return (p);
	}
	return (NULL);
}
