/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_left_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:52:36 by btammara          #+#    #+#             */
/*   Updated: 2021/03/23 10:56:17 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void    ft_left_redirect(t_args *args, int counter)
{
	t_redirect  *tmp_red;
    int         fd_red;
    
    tmp_red = args->redir_head;
    while (1)
    {
        if (!ft_strncmp(tmp_red->type, "<", 1))
            counter++;
        if (counter == args->left_redir)
            break ;
        tmp_red = tmp_red->next;
    }
    if ((fd_red = open(tmp_red->file_name, O_RDONLY)) == -1)
    {
        write(2, "my_bash: \n", 10);
        write(2, tmp_red->file_name, ft_strlen(tmp_red->file_name));
        write(2, ": Error (change it)\n", 20);
    }
    if (dup2(fd_red, 0) == -1)
        write(2, "dup2 error\n", 11);
    close(fd_red);
}