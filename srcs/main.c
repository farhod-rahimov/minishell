/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:39:57 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 13:30:53 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_struct strct;
	strct.args_head = NULL;
	strct.exit_value = 0;
	int fd;


	if (argc != 1)
		return (-1); // minishell doesn't launch with arguments
	g_flags.signal_c = 0;
	fd = open(HISTFILE, O_CREAT, 00777);
	close(fd);
	signal(SIGINT, ft_interrupt);
	signal(SIGQUIT, ft_quit);
	ft_structure_env(&strct, env);
	strct.initial_fd[0] = dup(0);
	strct.initial_fd[1] = dup(1);
	ft_term(&strct);

//	while (ft_show_prompt(&strct, 1) != -1)
//		;
	return (0);
}

