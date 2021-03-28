/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_env_var_ends.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:56:01 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 17:50:12 by btammara         ###   ########.fr       */
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

static	int		part1_env_var_dev_arg(char **arg, char *str, int *i)
{
	ft_push_back_char(arg, str[(*i)++]);
	return (0);
}

static	void	ft_env_var_divide_to_arguments(t_struct *strct, \
			t_args **cur_t_arg, char *str, char *arg)
{
	char	*tmp;
	int		flag;
	int		i;

	flag = 0;
	i = ft_skip_spaces(str, 0);
	while (str[i])
	{
		if (str[i] == ' ')
		{
			tmp = arg;
			ft_copy_str_to_structure_t_args(strct, \
				cur_t_arg, arg, strct->n_i++);
			free(tmp);
			arg = ft_strdup_new("");
			i = ft_skip_spaces(str, i);
			flag = 1;
		}
		else
			flag = part1_env_var_dev_arg(&arg, str, &i);
	}
	if (!flag)
		ft_copy_str_to_structure_t_args(strct, cur_t_arg, arg, strct->n_i++);
	free(arg);
}

static	int		part1_parse_till_env_ends(t_struct *strct, int i, char **str)
{
	char	*env_key;

	if (ft_isdigit(strct->parsed_str[i]))
		(*str) = ft_create_str_from_2_char(strct->parsed_str[i++], '\0');
	else
	{
		(*str) = ft_strdup_new("");
		while (strct->parsed_str[i] && \
		(ft_isalnum(strct->parsed_str[i]) || strct->parsed_str[i] == '_'))
			ft_push_back_char(str, strct->parsed_str[i++]);
	}
	env_key = *str;
	*str = ft_get_env_var_value(env_key, strct);
	free(env_key);
	return (i);
}

int				ft_parse_str_till_env_var_ends(t_args **cur_t_arg, \
								int i, t_struct *strct)
{
	char	*str;

	i = part1_parse_till_env_ends(strct, i, &str);
	if (((*cur_t_arg)->arg) && str[0] && \
	(!ft_strcmp((*cur_t_arg)->arg[0], "export") || \
	!ft_strcmp((*cur_t_arg)->arg[0], "unset")))
		ft_copy_str_to_structure_t_args(strct, cur_t_arg, str, strct->n_i++);
	else if (str[0])
		ft_env_var_divide_to_arguments(strct, cur_t_arg, \
			str, ft_strdup_new(""));
	free(str);
	i = ft_skip_spaces(strct->parsed_str, i);
	if (!(*cur_t_arg)->arg)
	{
		i = ft_skip_spaces(strct->parsed_str, i);
		if (strct->parsed_str[i] == ';')
			i++;
		i = ft_skip_spaces(strct->parsed_str, i);
		if (!strct->parsed_str[i])
			ft_free_t_args(cur_t_arg);
		return (i);
	}
	i = ft_check_if_new_list_or_arg_is_needed(strct, cur_t_arg, i);
	return (i);
}
