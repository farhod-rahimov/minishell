/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_left_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:52:36 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 15:31:33 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static	int	ft_wrong_redirect(void)
{
	write(2, "my_bash :", 9);
	write(2, " ambiguous redirect\n", 20);
	return (-1);
}

int			ft_left_redirect(t_struct *strct, t_args *args, int counter)
{
	t_redirect	*tmp_red;
	int			fd_red;

	tmp_red = args->redir_head;
	while (1)
	{
		if (tmp_red->file_name == NULL)
			return (ft_wrong_redirect());
		if (!ft_strncmp(tmp_red->type, "<", 1))
			counter++;
		if (counter == args->left_redir)
			break ;
		tmp_red = tmp_red->next;
	}
	if ((fd_red = open(tmp_red->file_name, O_RDONLY)) == -1)
	{
		ft_errno_error(strct, tmp_red->file_name);
		args->redir_flag = -1;
		return (0);
	}
	if (dup2(fd_red, 0) == -1)
		ft_dup2_error(strct);
	close(fd_red);
	return (0);
}
