/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 08:16:38 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 08:22:29 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_print_output(void)
{
    int fd_output;
    int ret;
    char buf[100];
    
	if ((fd_output = open(OUTPUT, O_RDONLY)) == -1)
		write (2, "cannot open /tmp/minishell_output.txt", 37);

    while ((ret = read(fd_output, buf, 100)) && ret != -1)
        write(1, buf, ret);
}