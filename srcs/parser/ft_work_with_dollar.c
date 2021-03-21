/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_with_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:03:57 by btammara          #+#    #+#             */
/*   Updated: 2021/03/21 09:59:55 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*ft_create_str_from_2_char(char c1, char c2);

int				ft_work_with_dollar(t_args **current_t_arg, int i, t_struct *strct)
{
	char	*str;
	char	*tmp;
	// add $?	
	str = ft_create_str_from_2_char('$', '\0');
	
	if (strct->parsed_str[i] != '\"' && strct->parsed_str[i] != '\'' && strct->parsed_str[i] != ';' && strct->parsed_str[i] != '|' \
			&& strct->parsed_str[i] != ' ' && strct->parsed_str[i] != '>' && strct->parsed_str[i] != '<')
	{
		tmp = str;
		str = ft_create_str_from_2_char('$', strct->parsed_str[i++]);
		free(tmp);
	}

	if ((ft_copy_str_to_structure_t_args(current_t_arg, str, strct->n_i)) == -1)	// n_i++
		return (-1); //malloc error
	
	free(str);

	i = ft_check_if_new_list_or_arg_is_needed(strct, current_t_arg, i);
	return (i);
}

static	char	*ft_create_str_from_2_char(char c1, char c2)
{
	char	*str;

	if ((str = (char *)malloc(sizeof(char) * 3)) == NULL)
		ft_error();
	str[0] = c1;
	str[1] = c2;
	str[2] = '\0';
	return (str);
}
