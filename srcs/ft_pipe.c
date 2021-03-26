/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:48:19 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 19:02:57 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_struct *strct, int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		ft_dup2_error(strct);
	if (dup2(fd_pipe[1], 1) == -1)
		ft_dup2_error(strct);
}

void	ft_close_pipe_01_dup_initial_0(int fd_pipe[2], t_struct *strct)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (dup2(strct->initial_fd[0], 0) == -1)
		ft_dup2_error(strct);
}

void	ft_close_pipe_01_dup_initial_1(int fd_pipe[2], t_struct *strct)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (dup2(strct->initial_fd[1], 1) == -1)
		ft_dup2_error(strct);
}
