/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:46:11 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 19:32:57 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*ft_strjoin_new(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*p;

	if (s1 == NULL)
	{
		p = ft_strdup_new(s2);
		return (p);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	if ((p = (char *)malloc((len + 1) * sizeof(char))) == NULL)
		ft_write_malloc_error();
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
