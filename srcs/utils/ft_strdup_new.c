/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:24:40 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 19:32:53 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_new(const char *s1)
{
	char					*p;
	unsigned long long int	i;
	unsigned long long int	a;

	i = 0;
	a = 0;
	while (s1[i] != '\0')
		i++;
	if ((p = (char *)malloc((i + 1) * sizeof(char))) == NULL)
		ft_write_malloc_error();
	while (a < i)
	{
		p[a] = s1[a];
		a++;
	}
	p[i] = '\0';
	return (p);
}
