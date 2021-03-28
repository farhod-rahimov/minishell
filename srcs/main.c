/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:39:57 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 10:31:23 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_struct	strct;
	int			fd;

	(void)argv;
	strct.args_head = NULL;
	strct.exit_value = 0;
	if (argc != 1)
		return (-1);
	g_signal = 0;
	if ((fd = open(HISTFILE, O_CREAT, 00777)) == -1)
		ft_errno_error(&strct, HISTFILE);
	close(fd);
	signal(SIGINT, ft_interrupt);
	signal(SIGQUIT, ft_quit);
	ft_structure_env(&strct, env);
	strct.initial_fd[0] = dup(0);
	strct.initial_fd[1] = dup(1);
	ft_term(&strct);
	return (0);
}
