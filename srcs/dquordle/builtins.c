/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:37:50 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:37:52 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pwd(int *exit_value)
{
	char *buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	*exit_value = 0;
}

static int	ft_is_flagn(char *str)
{
	int i;

	if (str[0] == '-')
	{
		i = 1;
		while (str[i] && str[i] == 'n')
			i++;
		if (!str[i])
			return (1);
	}
	return (0);
}

static void	ft_echo(char **arg, int *exit_value)
{
	int i;
	int n;

	n = 0;
	i = 1;
	while (arg[i] && ft_is_flagn(arg[i]))
		n += ++i;
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
	*exit_value = 0;
}

int			buildin(char **arg, t_env **head, int *exit_value)
{
	if (!ft_strcmp(arg[0], "echo"))
		ft_echo(arg, exit_value);
	else if (!ft_strcmp(arg[0], "pwd"))
		ft_pwd(exit_value);
	else if (!ft_strcmp(arg[0], "cd"))
		ft_cd(arg, head, exit_value);
	else if (!ft_strcmp(arg[0], "env"))
		ft_env(arg, *head, exit_value);
	else if (!ft_strcmp(arg[0], "export"))
		ft_export(arg, head, exit_value);
	else if (!ft_strcmp(arg[0], "unset"))
		ft_unset(arg, head, exit_value);
	else if (!ft_strcmp(arg[0], "exit"))
		ft_exit(arg, exit_value);
	else
		return (0);
	return (1);
}
