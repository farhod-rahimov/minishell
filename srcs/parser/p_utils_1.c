/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:20:25 by btammara          #+#    #+#             */
/*   Updated: 2021/03/17 17:27:14 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_args	*ft_create_new_t_args(t_struct *strct, t_args *prev_t_args)
{
	t_args *new_t_args;

	if ((new_t_args = (t_args *)malloc(sizeof(t_args))) == NULL)
		return (NULL);
	new_t_args->next = NULL;
		
	if (prev_t_args != NULL)
		prev_t_args->next = new_t_args;

	strct->n_i = 0;
	
	return (new_t_args);
}

int ft_check_if_new_list_is_needed(t_struct *strct, t_args **current_t_arg, int i)
{
	while (strct->parsed_str[i] == ' ')
		i++;
	if (strct->parsed_str[i] == ';')
	{
		i++;
		if ((*current_t_arg = ft_create_new_t_args(strct, *current_t_arg)) == NULL)
			return (-1);
	}
	return (i);
}

char	*ft_add_back_str(char *str, int k, char c)
{
	char *old_str;
	
	str[k - 1] = c;
	str[k++] = '\0';
	old_str = str;

	if ((str = (char *)malloc(sizeof(char) * (k + 1))) == NULL)
		return (NULL);
	ft_copy_old_str(old_str, str);
	free(old_str);
	return (str);
}

int		ft_copy_str_to_structure_args(t_args *tmp, char *str, int n_i)
{
	char **tmp_arg; // tmp->arg
	
	if (n_i == 0)
	{
		if ((tmp->arg = (char **)malloc(sizeof(char *) * (n_i + 2))) == NULL)
			return (-1);
		if ((tmp->arg[n_i] = ft_strdup(str)) == NULL) // n_i = 0
			return (-1);
		tmp->arg[n_i + 1] = NULL;
		return (0);
	}
	
	tmp_arg = tmp->arg;
	if ((tmp->arg = (char **)malloc(sizeof(char *) * (n_i + 2))) == NULL) // n_i for old strs, 1 for new str, 1 for NULL
		return (-1);
	if ((ft_copy_old_arg_n_i_of_tmp(tmp, tmp_arg, n_i)) == -1)
		return (-1);
	if ((tmp->arg[n_i] = ft_strdup(str)) == NULL)
		return (-1);
	tmp->arg[n_i + 1] = NULL;
	ft_free_splited_array(tmp_arg, n_i);
	return (0);
}

int		ft_copy_old_arg_n_i_of_tmp(t_args *tmp, char **tmp_arg, int n_i)
{
	int tmp_n_i;

	tmp_n_i = 0;
	while (tmp_n_i < n_i)
	{
		if ((tmp->arg[tmp_n_i] = ft_strdup(tmp_arg[tmp_n_i])) == NULL)
			return (-1);
		tmp_n_i++;
	}
	return (0);
}