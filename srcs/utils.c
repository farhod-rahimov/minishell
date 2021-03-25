/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:18:08 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 11:19:12 by btammara         ###   ########.fr       */
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