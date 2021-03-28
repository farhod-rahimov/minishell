/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structure_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:21:41 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 19:00:26 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static	void	ft_fill_t_env_list(t_env *env_list, char **env, int i, int k)
{
	if ((env_list->key = ft_substr(env[i], 0, k)) == NULL)
		ft_write_malloc_error();
	env_list->value = NULL;
	if (env[i][k] == '=')
		if ((env_list->value = ft_substr(env[i], ++k, \
		ft_strlen(env[i]))) == NULL)
			ft_write_malloc_error();
}

static void		ft_env_i(t_struct *strct)
{
	char *value;

	strct->env_head->key = ft_strdup_new("PWD");
	value = NULL;
	if (!(strct->env_head->value = getcwd(value, 0)))
		ft_write_malloc_error();
	ft_new_env(&(strct->env_head), "SHLVL", "1");
}

void			ft_structure_env(t_struct *strct, char **env)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;
	int		k;

	if ((strct->env_head = (t_env *)malloc(sizeof(t_env))) == NULL)
		ft_write_malloc_error();
	tmp = strct->env_head;
	tmp->next = NULL;
	i = 0;
	while (env[i])
	{
		k = 0;
		if (i > 0)
			tmp = ft_create_new_t_env(prev);
		while (env[i][k] != '=' && env[i][k] != '\0')
			k++;
		ft_fill_t_env_list(tmp, env, i, k);
		prev = tmp;
		i++;
	}
	if (!env[0])
		ft_env_i(strct);
	ft_get_path_to_bins(strct);
	ft_change_shell_level(strct->env_head);
}
