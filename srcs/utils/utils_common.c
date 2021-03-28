/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:18:08 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 19:47:38 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_copy_old_str(char *old_buf, char *new_buf)
{
	int	len;
	int	i;

	len = ft_strlen(old_buf);
	i = 0;
	while (i < len)
	{
		new_buf[i] = old_buf[i];
		i++;
	}
	new_buf[i] = '\0';
}

int		ft_remove_back_slash(char **str, int i)
{
	char	*tmp;
	int		initial_i;

	tmp = *str;
	initial_i = i;
	while ((*str)[i])
	{
		(*str)[i] = tmp[i + 1];
		i++;
	}
	return (++initial_i);
}

void	ft_push_back_char(char **str, char c)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*str);
	tmp = *str;
	if ((*str = (char *)malloc(sizeof(char) * (len + 2))) == NULL)
		ft_write_malloc_error();
	ft_strcopy(*str, tmp);
	(*str)[len] = c;
	(*str)[len + 1] = '\0';
	free(tmp);
	return ;
}

void	ft_strcopy(char *dst, char *src)
{
	int i;
	int max;

	i = 0;
	max = ft_strlen(src);
	while (i < max)
	{
		dst[i] = src[i];
		i++;
	}
}

int		ft_skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}
