/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arg_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 19:05:54 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 19:38:27 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	part1_check_new(t_struct *strct, t_args **cur_t_arg, int i)
{
	if (strct->parsed_str[i] == ';')
		ft_work_with_t_arg_lists(strct, cur_t_arg);
	if (strct->parsed_str[i] == '|')
	{
		if ((*cur_t_arg)->prev)
		{
			if ((*cur_t_arg)->prev->pipe)
				(*cur_t_arg)->pipe += (*cur_t_arg)->prev->pipe + 1;
			else
				(*cur_t_arg)->pipe = 1;
		}
		else
			(*cur_t_arg)->pipe = 1;
	}
	i = ft_skip_spaces(strct->parsed_str, ++i);
	if (strct->parsed_str[i] != '\0')
		*cur_t_arg = ft_create_new_t_args(strct, *cur_t_arg);
	return (i);
}

static	int	part2_check_new(t_struct *strct, t_args **cur_t_arg, int i)
{
	if (strct->parsed_str[i] == '>' && strct->parsed_str[i + 1] == '>')
	{
		i++;
		ft_push_back_redir_list(cur_t_arg, \
			(*cur_t_arg)->redir_head, ">>", NULL);
	}
	else if (strct->parsed_str[i] == '>')
		ft_push_back_redir_list(cur_t_arg, (*cur_t_arg)->redir_head, ">", NULL);
	else if (strct->parsed_str[i] == '<')
		ft_push_back_redir_list(cur_t_arg, (*cur_t_arg)->redir_head, "<", NULL);
	i++;
	return (i);
}

int			ft_check_if_new_list_or_arg_is_needed(t_struct *strct, \
					t_args **cur_t_arg, int i)
{
	int	len;

	if (i >= (len = ft_strlen(strct->parsed_str)))
		return (len);
	if (strct->parsed_str[i] == ' ')
		strct->n_i++;
	i = ft_skip_spaces(strct->parsed_str, i);
	if (strct->parsed_str[i] == ';' || strct->parsed_str[i] == '|')
		i = part1_check_new(strct, cur_t_arg, i);
	else if (strct->parsed_str[i] == '>' || strct->parsed_str[i] == '<')
		i = part2_check_new(strct, cur_t_arg, i);
	return (i);
}

void		ft_copy_str_to_structure_t_args(t_struct *strct, \
				t_args **tmp, char *str, int n_i)
{
	char	**tmp_arg;

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
	ft_free_two_dimensional_array(tmp_arg);
}
