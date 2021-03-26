/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_it_ends.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:58:19 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 15:22:29 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				ft_parse_str_till_it_ends(t_args **current_t_arg, int i, t_struct *strct)
{
	char	*str;
	
	str = ft_strdup_new("");
	while (strct->parsed_str[i] && strct->parsed_str[i] != ' ' && strct->parsed_str[i] != ';' && strct->parsed_str[i] != '\'' && strct->parsed_str[i] != '\"' \
			&& strct->parsed_str[i] != '$' && strct->parsed_str[i] != '|' && strct->parsed_str[i] != '>' && strct->parsed_str[i] != '<')
	{
       if (strct->parsed_str[i] == '\\')
			i++;
		ft_push_back_char(&str, strct->parsed_str[i++]);
	}
	
	ft_copy_str_to_structure_t_args(strct, current_t_arg, str, strct->n_i);	// n_i++
	free(str);

	i = ft_check_if_new_list_or_arg_is_needed(strct, current_t_arg, i);
	return (i);
}