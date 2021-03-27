/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 19:05:54 by btammara          #+#    #+#             */
/*   Updated: 2021/03/27 13:58:31 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_tolower_str(char *str);

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
		ft_free_arg(tmp->arg);
		ft_free_redir(tmp->redir_head);
		free(tmp);
		tmp = NULL;
	}
}

int ft_check_if_new_list_or_arg_is_needed(t_struct *strct, t_args **current_t_arg, int i)
{
    int len;
    
    if (i >= (len = ft_strlen(strct->parsed_str)))
        return (len);
	if (strct->parsed_str[i] == ' ')
		strct->n_i++;
	i = ft_skip_spaces(strct->parsed_str, i);
	if (strct->parsed_str[i] == ';' || strct->parsed_str[i] == '|')
	{
		if (strct->parsed_str[i] == ';')
		{
			ft_print_devided_args(*current_t_arg);
			ft_work_with_t_arg_lists(strct, current_t_arg);
		}
		if (strct->parsed_str[i] == '|')
		{
			if ((*current_t_arg)->prev)
			{
				if ((*current_t_arg)->prev->pipe)
					(*current_t_arg)->pipe += (*current_t_arg)->prev->pipe + 1;
				else
					(*current_t_arg)->pipe = 1;
			}
			else
				(*current_t_arg)->pipe = 1;
		}
		i = ft_skip_spaces(strct->parsed_str, ++i);
		// if (strct->parsed_str[i] != '\0')
			*current_t_arg = ft_create_new_t_args(strct, *current_t_arg);
	}
	else if (strct->parsed_str[i] == '>' || strct->parsed_str[i] == '<')
	{
		if (strct->parsed_str[i] == '>' && strct->parsed_str[i + 1] == '>')
		{
			i++;
			ft_push_back_redir_list(current_t_arg, (*current_t_arg)->redir_head, ">>", NULL);
		}
		else if (strct->parsed_str[i] == '>')
			ft_push_back_redir_list(current_t_arg, (*current_t_arg)->redir_head, ">", NULL);
		else if (strct->parsed_str[i] == '<')
			ft_push_back_redir_list(current_t_arg, (*current_t_arg)->redir_head, "<", NULL);
		i++;
	}
	return (i);
}

void		ft_copy_str_to_structure_t_args(t_struct *strct, t_args **tmp, char *str, int n_i)
{
	char	**tmp_arg; // tmp->arg
	
	tmp_arg = (*tmp)->arg;

	if ((*tmp)->redir_flag)
	{
		ft_push_back_redir_list(tmp, (*tmp)->redir_head, NULL, str);
		strct->n_i -= 1;
		return ;
	}
	if (tmp_arg == NULL)
	{
		if (((*tmp)->arg = (char **)malloc(sizeof(char *) * 2)) == NULL)
			ft_write_malloc_error();
		(*tmp)->arg[0] = ft_strdup_new(str);
		(*tmp)->arg[1] = NULL;
		return ;
	}
	ft_tolower_str((*tmp)->arg[0]);
	if (((*tmp)->arg = (char **)malloc(sizeof(char *) * (n_i + 2))) == NULL)
		ft_write_malloc_error();
	ft_copy_old_arg_to_new(tmp, tmp_arg, n_i);
	(*tmp)->arg[n_i] = ft_strjoin_new(tmp_arg[n_i], str);
	(*tmp)->arg[n_i + 1] = NULL;
	ft_free_arg(tmp_arg);
}

static	void	ft_tolower_str(char *str)
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

void	ft_free_arg(char **tmp_arg)
{
	int i;

	i = 0;
	if (tmp_arg == NULL)
		return ;
	while (tmp_arg[i])
		free(tmp_arg[i++]);
	// free(tmp_arg[i]);
	free(tmp_arg);
}