/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_with_t_arg_lists_part_1.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:46:27 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 19:29:42 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	**part1_work_with_lists(t_struct *strct, \
		t_args **cur_t_arg, t_args **current_t_arg_head)
{
	char	**env;

	if ((*cur_t_arg) == NULL)
		return (NULL);
	if ((*cur_t_arg)->arg == NULL)
		return (NULL);
	env = ft_create_env(strct->env_head);
	ft_free_two_dimensional_array(strct->path_to_bins);
	ft_get_path_to_bins(strct);
	while ((*cur_t_arg)->prev != NULL)
		*cur_t_arg = (*cur_t_arg)->prev;
	(*current_t_arg_head) = *cur_t_arg;
	return (env);
}

void			ft_work_with_t_arg_lists(t_struct *strct, t_args **cur_t_arg)
{
	t_args	*current_t_arg_head;
	int		fd_pipe[2];
	char	**env;

	if ((env = part1_work_with_lists(strct, cur_t_arg, \
				&current_t_arg_head)) == NULL)
		return ;
	while (*cur_t_arg)
	{
		if (ft_check_redirections(*cur_t_arg, strct, env) == -1)
			return ;
		ft_check_pipe(*cur_t_arg, strct, env, fd_pipe);
		if ((*cur_t_arg)->left_redir)
			if (dup2(strct->initial_fd[0], 0) == -1)
				ft_dup2_error(strct);
		if (((*cur_t_arg) = (*cur_t_arg)->next) == NULL)
		{
			ft_close_pipe_01_dup_initial_0(fd_pipe, strct);
			break ;
		}
		ft_check_if_reset_01fds_needed(*cur_t_arg, strct, fd_pipe);
	}
	ft_free_two_dimensional_array(env);
	ft_free_t_args(&current_t_arg_head);
}

int				ft_exec_build_in(t_args *tmp, t_env **head, t_struct *strct)
{
	if (tmp->redir_flag == -1)
		return (0);
	return (buildin(tmp->arg, head, &(strct->exit_value)));
}
