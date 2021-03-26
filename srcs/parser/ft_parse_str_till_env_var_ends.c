/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_env_var_ends.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:56:01 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 17:09:00 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*ft_get_env_var_value(char *env_var, t_struct *strct)
{
	t_env	*tmp;

	tmp = strct->env_head;
	while (tmp)
	{
		if (!ft_strncmp(env_var, tmp->key, \
		ft_strlen(env_var) + ft_strlen(tmp->key)))
		{
			env_var = ft_strdup_new(tmp->value);
			return (env_var);
		}
		tmp = tmp->next;
	}
	env_var = ft_strdup_new("");
	return (env_var);
}

int				ft_parse_str_till_env_var_ends(t_args **current_t_arg, \
								int i, t_struct *strct)
{
	char	*str;
	char	*env_key;

	str = ft_strdup_new("");
	while (strct->parsed_str[i] && \
	(ft_isalnum(strct->parsed_str[i]) || strct->parsed_str[i] == '_'))
		ft_push_back_char(&str, strct->parsed_str[i++]);
	env_key = str;
	str = ft_get_env_var_value(env_key, strct);
	free(env_key);
	ft_copy_str_to_structure_t_args(strct, current_t_arg, str, strct->n_i);
	free(str);
	i = ft_check_if_new_list_or_arg_is_needed(strct, current_t_arg, i);
	return (i);
}
