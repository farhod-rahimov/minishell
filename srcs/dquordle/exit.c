/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:38:10 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:38:11 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isnum(char *str)
{
	int i;
	int s;

	i = 0;
	s = 0;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		s += ++i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if ((i > 20 && s == 1) || (i > 19 && s == 0))
		return (0);
	return (1);
}

static void	ft_err_nar(char *str)
{
	write(2, "exit: ", 6);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

static int	ft_atol(char *str)
{
	unsigned long long int	num;
	unsigned long long int	num2;
	int						i;
	int						m;

	i = 0;
	num = 0;
	m = 0;
	num2 = -1;
	if (str[i] == '-' || str[i] == '+')
		m += str[i++] - '+';
	while (str[i])
	{
		num *= 10;
		num += str[i++] - 48;
	}
	if (num > num2 / 2 + 1 || (num == num2 / 2 + 1 && m == 0))
		ft_err_nar(str);
	if (m != 0)
		num = num2 / 2 + 1 - num;
	return (num % 256);
}

void		ft_exit(char **arg, int *exit_value)
{
	int ex_num;

	if (!arg[1])
		exit(*exit_value);
	if (ft_isnum(arg[1]) == 0)
		ft_err_nar(arg[1]);
	ex_num = ft_atol(arg[1]);
	if (!arg[2])
		exit(ex_num);
	else
	{
		write(2, "exit: too many arguments\n", 25);
		*exit_value = 1;
	}
}
