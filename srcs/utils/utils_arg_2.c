/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arg_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 19:05:54 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 19:33:13 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_args	*ft_create_new_t_args(t_struct *strct, t_args *prev_t_args)
{
	t_args *new_t_args;

	if ((new_t_args = (t_args *)malloc(sizeof(t_args))) == NULL)
		ft_write_malloc_error();
	new_t_args->next = NULL;
	new_t_args->prev = NULL;
	new_t_args->arg = NULL;
	new_t_args->redir_head = NULL;
	new_t_args->pipe = 0;
	new_t_args->right_redir = 0;
	new_t_args->left_redir = 0;
	new_t_args->redir_flag = 0;
	if (prev_t_args != NULL)
	{
		prev_t_args->next = new_t_args;
		new_t_args->prev = prev_t_args;
	}
	strct->n_i = 0;
	return (new_t_args);
}

void	ft_free_t_args(t_args **head)
{
	t_args *tmp;

	while ((*head))
	{
		tmp = (*head);
		(*head) = (*head)->next;
		ft_free_two_dimensional_array(tmp->arg);
		ft_free_redir(tmp->redir_head);
		free(tmp);
		tmp = NULL;
	}
}

void	ft_tolower_str(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		return ;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

int		ft_copy_old_arg_to_new(t_args **new_arg, char **old_arg, int n_i)
{
	int		i;

	i = 0;
	while (i < n_i)
	{
		(*new_arg)->arg[i] = ft_strdup_new(old_arg[i]);
		i++;
	}
	return (0);
}

void	ft_free_two_dimensional_array(char **tmp_arg)
{
	int i;

	i = 0;
	if (tmp_arg == NULL)
		return ;
	while (tmp_arg && tmp_arg[i])
		free(tmp_arg[i++]);
	free(tmp_arg);
}
