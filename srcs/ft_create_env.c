/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:26:49 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 09:41:11 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_join_key_and_value(t_env *tmp, char **env);
int			ft_get_env_size(t_env *tmp);

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
		if (ft_join_key_and_value(tmp, &(env[i])) != -1)
			i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

static int ft_join_key_and_value(t_env *tmp, char **env)
{
	char *tmp_str;
	
	if (tmp->value == NULL)
		return (-1);
	if ((*env = ft_strjoin(tmp->key, "=")) == NULL)
		ft_error();
	tmp_str = *env;
	if ((*env = ft_strjoin(*env, tmp->value)) == NULL)
		ft_error();
	free(tmp_str);
	return (0);
}

int  ft_get_env_size(t_env *tmp)
{
	int i;

	i = 1;
	while (tmp)
	{
		if (tmp->value)
			i++;
		tmp = tmp->next;
	}
	return(i);
}