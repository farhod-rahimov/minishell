/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_right_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:00:14 by btammara          #+#    #+#             */
/*   Updated: 2021/03/23 11:21:26 by btammara         ###   ########.fr       */
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
				printf("file name %s\n", tmp_red->file_name);
				if ((fd_red = open(tmp_red->file_name, O_CREAT | O_WRONLY | O_APPEND, 0766)) == -1)
					write(2, "fd errorr\n", 10);
				close(fd_red);
			}
			else
			{
				if ((fd_red = open(tmp_red->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0766)) == -1)
					write(2, "fd errorr\n", 10);
				close(fd_red);
			}
			counter++;
		}
		if (counter == args->right_redir)
			break ;
		tmp_red = tmp_red->next;
	}
	if (ft_strlen(tmp_red->file_name) == 2)
	{
		if ((fd_red = open(tmp_red->file_name, O_CREAT | O_WRONLY | O_APPEND, 0766)) == -1)
			write(2, "fd errorr\n", 10);
	}
	else
	{
		if ((fd_red = open(tmp_red->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0766)) == -1)
			write(2, "fd errorr\n", 10);
	}
	if (dup2(fd_red, 1) == -1)
		write(2, "dup2 error\n", 11);
	if (!(ft_exec_build_in(strct->args_head->arg, &strct->env_head)))
		ft_exec_bin(strct, args, strct->path_to_bins, env);
	close(fd_red);
	if (dup2(strct->initial_fd[1], 1) == -1)
		write(2, "dup2 ERROR\n", 11);
}