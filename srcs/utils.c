/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:18:08 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 17:01:48 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
