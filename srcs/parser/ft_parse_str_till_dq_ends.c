/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_dq_ends.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:56:32 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 17:25:24 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*ft_get_env_var_value(char *env_var, t_struct *strct)
{
	t_env	*tmp;

	tmp = strct->env_head;
	while (tmp)
	{
		if (!ft_strcmp(env_var, tmp->key))
		{
			env_var = ft_strdup_new(tmp->value);
			return (env_var);
		}
		tmp = tmp->next;
	}
	env_var = ft_strdup_new("");
	return (env_var);
}

static	void	ft_replace_env_key_to_its_value(char **str, char *env_value, \
							int start_env_var, int len_env_var)
{
	char *tmp1;
	char *tmp2;

	tmp1 = *str;
	if ((*str = ft_substr(*str, 0, start_env_var)) == NULL)
		ft_write_malloc_error();
	tmp2 = *str;
	*str = ft_strjoin_new(*str, env_value);
	free(tmp2);
	tmp2 = *str;
	*str = ft_strjoin_new(*str, tmp1 + start_env_var + len_env_var);
	free(tmp2);
	free(tmp1);
}

static	int		ft_get_env_var(char **str, int i, t_struct *strct)
{
	char	*env_var;
	char	*env_key;
	int		start_env_var;

	start_env_var = i - 1;
	if (ft_isdigit((*str)[i]))
		env_var = ft_create_str_from_2_char((*str)[i++], '\0');
	else
	{
		env_var = ft_strdup_new("");
		while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
			ft_push_back_char(&env_var, (*str)[i++]);
	}
	env_key = env_var;
	env_var = ft_get_env_var_value(env_var, strct);
	ft_replace_env_key_to_its_value(str, env_var, \
		start_env_var, ft_strlen(env_key) + 1);
	free(env_key);
	free(env_var);
	return (i);
}

static	void	ft_work_with_spec_sym(char **str, int i, t_struct *strct)
{
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && ((*str)[i + 1] == '\\' \
			|| (*str)[i + 1] == '$' || (*str)[i + 1] == '\"'))
		{
			i = ft_remove_back_slash(str, i);
			continue ;
		}
		else if ((*str)[i] == '$' && \
			(ft_isalnum((*str)[i + 1]) || (*str)[i + 1] == '_'))
		{
			i = ft_get_env_var(str, ++i, strct);
			continue ;
		}
		i++;
	}
}

int				ft_parse_str_till_dq_ends(t_args **cur_t_arg, \
								int i, t_struct *strct)
{
	char	*str;

	str = ft_strdup_new("");
	while (strct->parsed_str[i])
	{
		if (i > 0)
			if (strct->parsed_str[i] == '\"' \
			&& strct->parsed_str[i - 1] != '\\')
				break ;
		ft_push_back_char(&str, strct->parsed_str[i++]);
	}
	ft_work_with_spec_sym(&str, 0, strct);
	if (str[0] != '\0')
		ft_copy_str_to_structure_t_args(strct, cur_t_arg, str, strct->n_i);
	if (str[0] == '\0')
		strct->n_i--;
	i = ft_check_if_new_list_or_arg_is_needed(strct, cur_t_arg, ++i);
	free(str);
	return (i);
}
