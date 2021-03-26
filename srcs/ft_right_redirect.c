/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_right_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:00:14 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 18:51:03 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		open_file(t_struct *strct, t_redirect **tmp_red, char *redirect)
{
	int	fd_red;

	if (!ft_strcmp(redirect, ">>"))
	{
		if ((fd_red = open((*tmp_red)->file_name, \
		O_CREAT | O_WRONLY | O_APPEND, 0766)) == -1)
			ft_errno_error(strct, (*tmp_red)->file_name);
	}
	else
	{
		if ((fd_red = open((*tmp_red)->file_name, \
		O_CREAT | O_WRONLY | O_TRUNC, 0766)) == -1)
			ft_errno_error(strct, (*tmp_red)->file_name);
	}
	return (fd_red);
}

static	int		part1(t_struct *strct, t_redirect **tmp_red, \
						t_args *args, int counter)
{
	int fd_red;

	while (1)
	{
		if (!ft_strncmp((*tmp_red)->type, ">", 1))
		{
			if (ft_strlen((*tmp_red)->type) == 2)
				fd_red = open_file(strct, tmp_red, ">>");
			else
				fd_red = open_file(strct, tmp_red, ">");
			close(fd_red);
			counter++;
		}
		if (counter == args->right_redir)
			break ;
		(*tmp_red) = (*tmp_red)->next;
	}
	return (fd_red);
}

void			ft_right_redirect(t_struct *strct, t_args *args, \
							char **env, int counter)
{
	t_redirect	*tmp_red;
	int			fd_red;

	tmp_red = args->redir_head;
	fd_red = part1(strct, &tmp_red, args, counter);
	if (ft_strlen(tmp_red->type) == 2)
		fd_red = open_file(strct, &tmp_red, ">>");
	else
		fd_red = open_file(strct, &tmp_red, ">");
	if (dup2(fd_red, 1) == -1)
		ft_dup2_error(strct);
	if (!(ft_exec_build_in(args->arg, &strct->env_head, strct)))
		if (ft_strcmp(args->arg[0], ""))
			ft_exec_bin(strct, args, strct->path_to_bins, env);
	close(fd_red);
	if (dup2(strct->initial_fd[1], 1) == -1)
		ft_dup2_error(strct);
}
