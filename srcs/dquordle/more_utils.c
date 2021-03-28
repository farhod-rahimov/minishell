/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:38:40 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:38:41 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_append(char *old, char *new)
{
	char	*newest;
	int		i;
	int		j;

	if (!(newest = (char *)malloc(ft_strlen(old) + ft_strlen(new) + 1)))
		ft_write_malloc_error();
	j = 0;
	i = -1;
	while (old[++i])
		newest[i] = old[i];
	while (new[j])
		newest[i++] = new[j++];
	newest[i] = 0;
	free(old);
	return (newest);
}
