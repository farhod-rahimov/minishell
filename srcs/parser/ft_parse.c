/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:52:30 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 17:25:37 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_parse(t_struct *strct, t_args *tmp, int i)
{
	char	*str;

	str = strct->parsed_str;
	if (ft_check_syntax(strct, str) == -1)
		return (-1);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\"')
			i = ft_parse_str_till_dq_ends(&tmp, ++i, strct);
		else if (str[i] == '\'')
			i = ft_parse_str_till_sq_ends(&tmp, ++i, strct);
		else if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			i = ft_parse_str_till_env_var_ends(&tmp, ++i, strct);
		else if (str[i] == '$' && (!ft_isalnum(str[i + 1]) \
		&& str[i + 1] != '_'))
			i = ft_work_with_dollar(&tmp, ++i, strct);
		else
			i = ft_parse_str_till_it_ends(&tmp, i, strct);
	}
	free(str);
	ft_work_with_t_arg_lists(strct, &tmp);
	return (0);
}
