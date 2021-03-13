/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:52:30 by btammara          #+#    #+#             */
/*   Updated: 2021/03/13 10:54:57 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse(t_struct *strct, t_args *tmp, int i)
{
	char	*str;
	char	*tmp_str;
	int		k;

	k = 1;
	if ((str = (char *)malloc(sizeof(char) * k + 1)) == NULL)
		return (-1);
	
	while (strct->parsed_str[i] == ' ')
		i++;
	while (strct->parsed_str[i])
	{
		if (strct->parsed_str[i] == ';')
		{
			if (k == 1)
				return (-1); // "  ; parsed_str" or "  parsed str    ;  ;"
			
			if (i > 1)
				if (strct->parsed_str[i - 1] != ' ')
					if ((ft_copy_str_to_structure_args(tmp, str, strct->n, strct->n_i)) == -1)	
						return (-1); //malloc error
			
			if ((tmp = ft_create_new_t_args(tmp)) == NULL)
				return (-1);
			strct->n++;
			strct->n_i = 0;
			
			return (ft_parse(strct, tmp, ++i));
		}
		if (strct->parsed_str[i] == ' ')
		{
			if ((ft_copy_str_to_structure_args(tmp, str, strct->n, strct->n_i)) == -1)	
				return (-1); //malloc error
			strct->n_i++;
			return (ft_parse(strct, tmp, i));
		}

		str[k - 1] = strct->parsed_str[i];	
		str[k++] = '\0';
		tmp_str = str;
		if ((str = (char *)malloc(sizeof(char) * (k + 1))) == NULL)
			return (-1); //malloc error
		ft_copy_old_str(tmp_str, str);
		free(tmp_str);

		i++;
	}
	return (0);
}

int		ft_copy_str_to_structure_args(t_args *tmp, char *str, int n, int n_i)
{
	char **tmp_arg; // tmp->arg
	(void)n;
	
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
	if ((ft_copy_old_arg_n_i_of_tmp(tmp, tmp_arg, n, n_i)) == -1)
		return (-1);
	if ((tmp->arg[n_i] = ft_strdup(str)) == NULL)
		return (-1);
	tmp->arg[n_i + 1] = NULL;
	free(tmp_arg);  // не до конца правильно очищаю нужно кажду строку в этом 2-ух мерном массиве
	return (0);
}

int		ft_copy_old_arg_n_i_of_tmp(t_args *tmp, char **tmp_arg, int n, int n_i)
{
	int tmp_n_i;
	(void)n;

	tmp_n_i = 0;
	while (tmp_n_i < n_i)
	{
		if ((tmp->arg[tmp_n_i] = ft_strdup(tmp_arg[tmp_n_i])) == NULL)
			return (-1);
		tmp_n_i++;
	}
	return (0);
}

t_args	*ft_create_new_t_args(t_args *prev_t_args)
{
	t_args *new_t_args;

	if ((new_t_args = (t_args *)malloc(sizeof(t_args))) == NULL)
		return (NULL);
	new_t_args->next = NULL;
		
	if (prev_t_args != NULL)
		prev_t_args->next = new_t_args;
	
	return (new_t_args);
}

void	ft_print_devided_args(t_args *head)
{
	t_args	*tmp;
	int		i;

	tmp = head;
	i = 0;
	printf("--------------------\n");
	while (tmp)
	{
		while (tmp->arg[i])
		{
			printf("%s\n", tmp->arg[i]);
			i++;
		}
		printf("------------------------\n");
		i = 0;
		tmp = tmp->next;
	}
}
