/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_right_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:00:14 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 14:18:22 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_right_redirect(t_struct *strct, t_args *args, char **env, int counter)
{
	t_redirect	*tmp_red;
	int			fd_red;
 
	tmp_red = args->redir_head;
	while (1)
	{
		if (!ft_strncmp(tmp_red->type, ">", 1))
		{
			if (ft_strlen(tmp_red->type) == 2)
			{
				if ((fd_red = open(tmp_red->file_name, O_CREAT | O_WRONLY | O_APPEND, 0766)) == -1)
					ft_errno_error(strct, tmp_red->file_name);
				close(fd_red);
			}
			else
			{
				if ((fd_red = open(tmp_red->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0766)) == -1)
					ft_errno_error(strct, tmp_red->file_name);
				close(fd_red);
			}
			counter++;
		}
		if (counter == args->right_redir)
			break ;
		tmp_red = tmp_red->next;
	}
	if (ft_strlen(tmp_red->type) == 2)
	{
		if ((fd_red = open(tmp_red->file_name, O_CREAT | O_WRONLY | O_APPEND, 0766)) == -1)
			ft_errno_error(strct, tmp_red->file_name);
	}
	else
	{
		if ((fd_red = open(tmp_red->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0766)) == -1)
			ft_errno_error(strct, tmp_red->file_name);
	}
	if (dup2(fd_red, 1) == -1)
		ft_dup2_error(strct);
	if (!(ft_exec_build_in(args->arg, &strct->env_head, strct)))
		if (ft_strcmp(args->arg[0], ""))
			ft_exec_bin(strct, args, strct->path_to_bins, env);
	close(fd_red);
	if (dup2(strct->initial_fd[1], 1) == -1)
		ft_dup2_error(strct);
}