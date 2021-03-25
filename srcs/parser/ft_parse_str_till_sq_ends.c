/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_sq_ends.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:59:07 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 11:02:02 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				ft_parse_str_till_sq_ends(t_args **current_t_arg, int i, t_struct *strct, int k)
{
	char	*str;
	(void)k;
	
	if (!(str = ft_strdup("")))
		ft_error();
	while (strct->parsed_str[i] && strct->parsed_str[i] != '\'')
	{
		ft_push_back_char(&str, strct->parsed_str[i++]);
	}
	
	ft_copy_str_to_structure_t_args(strct, current_t_arg, str, strct->n_i);	// n_i++
	free(str);

	i = ft_check_if_new_list_or_arg_is_needed(strct, current_t_arg, ++i); // ++i for skipping the last 
	return (i);
}