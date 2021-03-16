/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:55:10 by btammara          #+#    #+#             */
/*   Updated: 2020/11/03 08:06:46 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	c_word(char const *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static	char	*w_malloc(char const *str, char c)
{
	char	*w;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (!(w = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		w[i] = str[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

static	char	**free_all(char **array, int i)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		a;
	char	**array;

	i = 0;
	a = 0;
	if (s == NULL)
		return (NULL);
	if (!(array = (char **)malloc(sizeof(char *) * (c_word(s, c) + 1))))
		return (NULL);
	while (s[a])
	{
		while (s[a] && s[a] == c)
			a++;
		if (s[a] && s[a] != c)
		{
			if ((array[i++] = w_malloc(&s[a], c)) == NULL)
				return (free_all(array, i));
			while (s[a] && s[a] != c)
				a++;
		}
	}
	array[i] = NULL;
	return (array);
}
