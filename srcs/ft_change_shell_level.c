/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_shell_level.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:14:21 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 11:23:50 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  void    ft_increment_shell_level(t_struct *strct, t_env **current_env);
static  void     ft_add_shell_level(t_struct *strct, t_env *env_head);

void	ft_change_shell_level(t_struct *strct, t_env *env_head)
{
	t_env	*tmp;
	int		flag;

	tmp = env_head;
	flag = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", ft_strlen(tmp->key) + ft_strlen("SHLVL")))
		{
			flag = 1;
			ft_increment_shell_level(strct, &tmp);
			break;
		}
		tmp = tmp->next;
	}
	if (!flag)
		ft_add_shell_level(strct, env_head);
}

static  void    ft_increment_shell_level(t_struct *strct, t_env **current_env)
{
	int     value;
	char    *tmp;

	value = ft_atoi((*current_env)->value);

	tmp = (*current_env)->value; 
	if (((*current_env)->value = ft_itoa(++value)) == NULL)
		ft_new_error(strct, 1, 1);
	free(tmp);
}

static  void     ft_add_shell_level(t_struct *strct, t_env *env_head)
{
	t_env *tmp;
	t_env *new;
	
	tmp = env_head;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			if ((new = ft_create_new_t_env(tmp)) == NULL)
				ft_new_error(strct, 1, 1);
			if ((new->key = ft_strdup("SHLVL")) == NULL)
				ft_new_error(strct, 1, 1);
			if ((new->value = ft_strdup("1")) == NULL)
				ft_new_error(strct, 1, 1);
		}
		tmp = tmp->next;
	}
}