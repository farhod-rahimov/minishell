/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_shell_level.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:14:21 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 17:35:54 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_increment_shell_level(t_env **current_env)
{
	int		value;
	char	*tmp;

	tmp = NULL;
	if (!((*current_env)->value))
		value = 0;
	else
	{
		value = ft_atoi((*current_env)->value);
		tmp = (*current_env)->value;
	}
	if (((*current_env)->value = ft_itoa(++value)) == NULL)
		ft_write_malloc_error();
	if (tmp)
		free(tmp);
}

static	void	ft_add_shell_level(t_env *env_head)
{
	t_env *tmp;
	t_env *new;

	tmp = env_head;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			new = ft_create_new_t_env(tmp);
			new->key = ft_strdup_new("SHLVL");
			new->value = ft_strdup_new("1");
			break ;
		}
		tmp = tmp->next;
	}
}

void			ft_change_shell_level(t_env *env_head)
{
	t_env	*tmp;
	int		flag;

	tmp = env_head;
	flag = 0;
	while (tmp)
	{
		if (!flag && !ft_strcmp(tmp->key, "SHLVL"))
		{
			flag = 1;
			ft_increment_shell_level(&tmp);
		}
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		tmp = tmp->next;
	}
	if (!flag)
		ft_add_shell_level(env_head);
}
