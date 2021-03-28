/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:52:30 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 18:45:46 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_parse(t_struct *strct, t_args *tmp, int i, char *str)
{
	if (ft_check_syntax(strct, str, -1, -1) == -1)
		return (-1);
	while (str[i])
	{
		i = ft_skip_spaces(str, i);
		if (!str[i] && !strct->n_i)
		{
			ft_free_t_args(&tmp);
			break ;
		}
		if (str[i] == '\"')
			i = ft_parse_str_till_dq_ends(&tmp, ++i, strct);
		else if (str[i] == '\'')
			i = ft_parse_str_till_sq_ends(&tmp, ++i, strct);
		else if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			i = ft_parse_str_till_env_var_ends(&tmp, ++i, strct);
		else if (str[i] == '$' && (!ft_isalnum(str[i + 1]) \
		&& str[i + 1] != '_'))
			i = ft_work_with_dollar(&tmp, ++i, strct);
		else if (str[i])
			i = ft_parse_str_till_it_ends(&tmp, i, strct);
	}
	free(str);
	ft_work_with_t_arg_lists(strct, &tmp);
	return (0);
}

void		ft_begin_parsing(t_struct *strct)
{
	t_args *tmp;

	tmp = strct->args_head;
	strct->args_head = ft_create_new_t_args(strct, NULL);
	ft_parse(strct, strct->args_head, 0, strct->parsed_str);
}
