/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_it_ends.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:58:19 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 17:25:24 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				ft_parse_str_till_it_ends(t_args **cur_t_arg, \
								int i, t_struct *strct)
{
	char	*str;
	char	*tmp;

	str = ft_strdup_new("");
	tmp = strct->parsed_str;
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != ';' \
	&& tmp[i] != '\'' && tmp[i] != '\"' && tmp[i] != '$' \
	&& tmp[i] != '|' && tmp[i] != '>' && tmp[i] != '<')
	{
		if (tmp[i] == '\\')
			i++;
		ft_push_back_char(&str, tmp[i++]);
	}
	ft_copy_str_to_structure_t_args(strct, cur_t_arg, str, strct->n_i);
	free(str);
	i = ft_check_if_new_list_or_arg_is_needed(strct, cur_t_arg, i);
	return (i);
}
