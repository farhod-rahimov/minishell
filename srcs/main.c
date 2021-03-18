/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:39:57 by btammara          #+#    #+#             */
/*   Updated: 2021/03/18 13:29:25 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_struct strct;
	strct.args_head = NULL;
	
	if (argc != 1)
		return (-1); // minishell doesn't launch with arguments
	if (ft_structure_env(&strct, env) == -1)
		return (-1);
	while (ft_show_prompt(&strct, 1) != -1)
		;
	return (0);
}

