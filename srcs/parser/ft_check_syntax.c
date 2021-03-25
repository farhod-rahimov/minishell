/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:09:39 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 10:57:27 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static	int		ft_skip_spaces(char *str, int i);
static	void	ft_free_if_error(t_struct *strct);
static	int		ft_print_stntax_error(t_struct *strct, char c);

int	ft_check_syntax(t_struct *strct, char *str)
{
	int		i;
	char	tmp;

	i = 0;
	while (str[i])
	{
		i = ft_skip_spaces(str, i);
		if (str[i] == ';' || str[i] == '|')
		{
			tmp = str[i];
			i = ft_skip_spaces(str, ++i);
			if (tmp == ';' && (str[i] == '|' || str[i] == ';'))
				return (ft_print_stntax_error(strct, str[i]));
			else if (tmp == '|' && str[i] == ';')
				return (ft_print_stntax_error(strct, str[i]));
		}
		i++;
	}
	return (0);
}

static	int ft_print_stntax_error(t_struct *strct, char c)
{
	write(2, "my_bash: syntax error near unexpected token '", 45);
	write(2, &c, 1);
	write(2, "'\n", 2);
	ft_free_if_error(strct);
	ft_new_error(strct, 258, 0);
	return (-1);
}

static int ft_skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

static	void	ft_free_if_error(t_struct *strct)
{
	free(strct->parsed_str);
	free(strct->args_head);
	strct->args_head = NULL;
}