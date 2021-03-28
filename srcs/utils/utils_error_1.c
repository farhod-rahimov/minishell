/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 19:08:57 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 19:45:19 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup2_error(t_struct *strct)
{
	char *error;

	error = "dup2 error\n";
	write(2, "my_bash: ", 9);
	write(2, error, ft_strlen(error));
	dup2(strct->initial_fd[0], 0);
	dup2(strct->initial_fd[1], 1);
	exit(1);
}

void	ft_errno_error(t_struct *strct, char *file_name)
{
	strct->exit_value = 1;
	write(2, "my_bash: ", 9);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	ft_write_malloc_error(void)
{
	write(2, "my_bash: ", 9);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(1);
}

void	ft_free_if_error(t_struct *strct)
{
	free(strct->parsed_str);
	free(strct->args_head);
	strct->args_head = NULL;
}
