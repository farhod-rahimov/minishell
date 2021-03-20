/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:26:49 by btammara          #+#    #+#             */
/*   Updated: 2021/03/20 16:29:32 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_join_key_and_value(t_env *tmp, char **env);
int  ft_get_env_size(t_env *tmp);

char	**ft_create_env(t_env *env_head)
{
	int     i;
	char    **env;
	t_env   *tmp;

	tmp = env_head;
	i = ft_get_env_size(tmp);
	if ((env = (char **)malloc(sizeof(char *) * i)) == NULL)
		ft_error();
	i = 0;
	while (tmp)
	{
		ft_join_key_and_value(tmp, &env[i++]);
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

static void ft_join_key_and_value(t_env *tmp, char **env)
{
	char *tmp_str;
	
	if (tmp->value == NULL)
		return ;
	if ((*env = ft_strjoin(tmp->key, "=")) == NULL)
		ft_error();
	tmp_str = *env;
	if ((*env = ft_strjoin(*env, tmp->value)) == NULL)
		ft_error();
	free(tmp_str);
}

int  ft_get_env_size(t_env *tmp)
{
	int i;

	i = 1;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return(i);
}