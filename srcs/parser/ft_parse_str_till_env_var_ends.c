// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_parse_str_till_env_var_ends.c                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/03/14 13:56:01 by btammara          #+#    #+#             */
// /*   Updated: 2021/03/18 09:28:00 by btammara         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// static	int		ft_get_env_var_value(t_struct *strct, t_args **current_t_arg, char *str);

// int				ft_parse_str_till_env_var_ends(t_args **current_t_arg, int i, t_struct *strct, int k)
// {
// 	char	*str;
// 	int		r;
	
// 	if ((str = (char *)malloc(sizeof(char) * (k + 1))) == NULL)
// 		return (-1);
	
// 	while (strct->parsed_str[i] && strct->parsed_str[i] != ';' && strct->parsed_str[i] != ' ')
// 	{
// 		if ((str = ft_add_back_str(str, k++, strct->parsed_str[i])) == NULL)
// 			return (-1);
// 		i++;
// 	}
	
// 	if ((r = ft_get_env_var_value(strct, current_t_arg, str)) == -1)  // -1 = malloc error
// 		return (-1);
// 	else if (r == -2) // -2 = key has no value
// 		if ((ft_copy_str_to_structure_args(*current_t_arg, "", strct->n_i++)) == -1)	// n_i++
// 			return (-1); //malloc error
		
// 	i = ft_check_if_new_list_is_needed(strct, current_t_arg, i);
// 	return (i);
// }

// int				ft_get_env_var_value(t_struct *strct, t_args **current_t_arg, char *str)
// {
// 	t_env *tmp;

// 	tmp = strct->env_head;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(str + 1, tmp->key, ft_strlen(str) + ft_strlen(tmp->key)))
// 		{
// 			free(str);
// 			if ((ft_copy_str_to_structure_args(*current_t_arg, tmp->value, strct->n_i++)) == -1)	// n_i++
// 				return (-1); //malloc error
// 			return (0);
// 		}
// 		tmp = tmp->next;
// 	}
// 	free(str);
// 	return (-2);
// }