/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:26:49 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 14:58:46 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_join_key_and_value(t_env *tmp, char **env);
int			ft_get_env_size(t_env *tmp);

char	**ft_create_env(t_struct *strct, t_env *env_head)
{
	int     i;
	char    **env;
	t_env   *tmp;

	tmp = env_head;
	i = ft_get_env_size(tmp);
	if ((env = (char **)malloc(sizeof(char *) * i)) == NULL)
		ft_new_error(strct, 1, 1);
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
	*env = ft_strjoin_new(tmp->key, "=");
	tmp_str = *env;
	*env = ft_strjoin_new(*env, tmp->value);
	free(tmp_str);
	return (0);
}

int  ft_get_env_size(t_env *tmp)
{
	int i;

	i = 1;
	while (tmp)
	{
		if (tmp->value != NULL)
			i++;
		tmp = tmp->next;
	}
	return(i);
}