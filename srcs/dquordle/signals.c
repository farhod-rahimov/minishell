/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:38:46 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:38:47 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_interrupt(int signal)
{
	pid_t	pid;
	int		status;

	(void)signal;
	pid = waitpid(0, &status, WNOHANG);
	if (pid == 0)
		g_signal = 2;
	else
	{
		write(1, "\nmy_bash% ", 10);
		g_signal = 1;
	}
}

void	ft_quit(int signal)
{
	pid_t	pid;
	int		status;

	(void)signal;
	pid = waitpid(0, &status, WNOHANG);
	if (pid == 0)
	{
		write(1, "Quit: 3\nmy_bash% ", 17);
		g_signal = 3;
	}
}
