/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:16:00 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 19:20:20 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_if_reset_01fds_needed(t_args *tmp, \
			t_struct *strct, int fd_pipe[2])
{
	if (tmp && tmp->prev && tmp->prev->pipe)
	{
		close(fd_pipe[1]);
		if (dup2(fd_pipe[0], 0) == -1)
			ft_dup2_error(strct);
		return ;
	}
	ft_close_pipe_01_dup_initial_0(fd_pipe, strct);
}

void	ft_check_pipe(t_args *tmp, t_struct *strct, char **env, int fd_pipe[2])
{
	if (tmp->arg)
	{
		if (tmp->pipe)
		{
			ft_pipe(strct, fd_pipe);
		}
		else if (tmp->prev)
		{
			if (tmp->prev->pipe)
				ft_close_pipe_01_dup_initial_1(fd_pipe, strct);
		}
		if (!tmp->right_redir)
			if (!(ft_exec_build_in(tmp, &strct->env_head, strct)))
				ft_exec_bin(strct, tmp, strct->path_to_bins, env);
	}
}

int		ft_check_redirections(t_args *tmp, t_struct *strct, char **env)
{
	if (tmp->prev != NULL)
	{
		if (tmp->left_redir && !tmp->prev->pipe)
			if (ft_left_redirect(strct, tmp, 0) == -1)
				return (-1);
	}
	else if (tmp->prev == NULL && tmp->left_redir)
		if (ft_left_redirect(strct, tmp, 0) == -1)
			return (-1);
	if (tmp->right_redir)
		if (ft_right_redirect(strct, tmp, env, 0) == -1)
			return (-1);
	return (0);
}
