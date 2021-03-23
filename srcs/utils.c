/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:18:08 by btammara          #+#    #+#             */
/*   Updated: 2021/03/20 14:41:18 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_splited_array(char **array, int n)
{
	int i;

	i = 0;
	while (i < n)
		free(array[i++]);
	free(array);
}

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