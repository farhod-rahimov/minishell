/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_with_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:03:57 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 18:46:00 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*ft_create_str_from_2_char(char c1, char c2)
{
	char	*str;

	if ((str = (char *)malloc(sizeof(char) * 3)) == NULL)
		ft_write_malloc_error();
	str[0] = c1;
	str[1] = c2;
	str[2] = '\0';
	return (str);
}

int				ft_work_with_dollar(t_args **cur_t_arg, \
							int i, t_struct *strct)
{
	char	*two_char;
	char	*str;
	char	*tmp;

	two_char = ft_create_str_from_2_char('$', '\0');
	str = strct->parsed_str;
	if (str[i] != '\"' && str[i] != '\'' && str[i] != ';' && str[i] != '|' \
	&& str[i] != ' ' && str[i] != '>' && str[i] != '<')
	{
		tmp = two_char;
		two_char = ft_create_str_from_2_char('$', str[i++]);
		free(tmp);
	}
	if (!ft_strcmp(two_char, "$?"))
	{
		tmp = two_char;
		two_char = ft_itoa(strct->exit_value);
		free(tmp);
	}
	ft_copy_str_to_structure_t_args(strct, cur_t_arg, two_char, strct->n_i);
	free(two_char);
	i = ft_check_if_new_list_or_arg_is_needed(strct, cur_t_arg, i);
	return (i);
}
