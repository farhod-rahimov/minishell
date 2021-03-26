/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 19:04:47 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 19:20:30 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env			*ft_create_new_t_env(t_env *prev)
{
	t_env *new;

	if ((new = (t_env *)malloc(sizeof(t_env))) == NULL)
		ft_write_malloc_error();
	prev->next = new;
	new->next = NULL;
	return (new);
}

int				ft_get_env_size(t_env *tmp)
{
	int i;

	i = 1;
	while (tmp)
	{
		if (tmp->value != NULL)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static	void	ft_add_slash_to_the_end_of_each_path_to_bins(t_struct *strct)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strct->path_to_bins[i])
	{
		tmp = strct->path_to_bins[i];
		strct->path_to_bins[i++] = ft_strjoin_new(tmp, "/");
		free(tmp);
	}
}

void			ft_get_path_to_bins(t_struct *strct)
{
	t_env *tmp;

	strct->path_to_bins = NULL;
	tmp = strct->env_head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)) == 0)
		{
			if ((strct->path_to_bins = ft_split(tmp->value, ':')) == NULL)
				ft_write_malloc_error();
			ft_add_slash_to_the_end_of_each_path_to_bins(strct);
		}
		tmp = tmp->next;
	}
}
