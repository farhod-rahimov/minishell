/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:09:39 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 09:26:54 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static	int		ft_skip_spaces(char *str, int i);
static	void	ft_free_if_error(t_struct *strct);

int	ft_check_syntax(t_struct *strct, char *str)
{
	(void)strct;
	int i;
	char tmp;

	i = 0;
	
	while (str[i])
	{
		i = ft_skip_spaces(str, i);
		if (str[i] == ';' || str[i] == '|')
		{
			tmp = str[i];
			i = ft_skip_spaces(str, i);
			if (tmp == ';' && (str[i] == '|' || str[i] == ';'))
			{
				write(2, "my_bash: syntax error near unexpected token '", 45);
				write(2, &str[i], 1);
				write(2, "'\n", 2);
				ft_free_if_error(strct);
				return (-1);
			}
			else if (tmp == '|' && str[i] == ';')
			{
				write(2, "my_bash: syntax error near unexpected token '", 45);
				write(2, &str[i], 1);
				write(2, "'\n", 2);
				ft_free_if_error(strct);
				return (-1);
			}
		}
		i++;
	}



	return (0);
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