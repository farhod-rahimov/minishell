/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_shell_level.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:14:21 by btammara          #+#    #+#             */
/*   Updated: 2021/03/20 15:24:43 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  void    ft_increment_shell_level(t_env **current_env);
static  void     ft_add_shell_level(t_env *env_head);

void	ft_change_shell_level(t_env *env_head)
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
			ft_increment_shell_level(&tmp);
			break;
		}
		tmp = tmp->next;
	}
	if (!flag)
		ft_add_shell_level(env_head);
}

static  void    ft_increment_shell_level(t_env **current_env)
{
	int     value;
	char    *tmp;

	value = ft_atoi((*current_env)->value);

	tmp = (*current_env)->value; 
	(*current_env)->value = ft_itoa(++value);
	free(tmp);
}

static  void     ft_add_shell_level(t_env *env_head)
{
	t_env *tmp;
	t_env *new;
	
	tmp = env_head;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			new = ft_create_new_t_env(tmp);
			new->key = ft_strdup("SHLVL");
			new->value = ft_strdup("1");
		}
		tmp = tmp->next;
	}
}