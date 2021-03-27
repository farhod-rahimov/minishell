/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:09:39 by btammara          #+#    #+#             */
/*   Updated: 2021/03/27 08:17:33 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_free_if_error(t_struct *strct)
{
	free(strct->parsed_str);
	free(strct->args_head);
	strct->args_head = NULL;
}

static	char	*ft_str_from_char(char c)
{
	char	*str;

	if ((str = (char *)malloc(sizeof(char) * 2)) == NULL)
		ft_write_malloc_error();
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static	int		ft_print_stntax_error(t_struct *strct, char c)
{
	char	*str;

	if (c == '\0')
		str = ft_strdup_new("newline");
	else
		str = ft_str_from_char(c);
	write(2, "my_bash: syntax error near unexpected token '", 45);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	ft_free_if_error(strct);
	strct->exit_value = 258;
	free(str);
	return (-1);
}

int				ft_check_syntax(t_struct *strct, char *str)
{
	int		i;
	char	tmp;
	int		s_q;
	int		d_q;
	int		first_time;

	i = 0;
	s_q = -1;
	d_q = -1;
	first_time = 0;
	while (str[i])
	{
		i = ft_skip_spaces(str, i);
		if (first_time++ == 0 && (str[i] == '|' || str[i] == ';'))
			return (ft_print_stntax_error(strct, str[i]));
		if (str[i] == '\\')
			i += 2;
		if (str[i] == '"' && s_q != -1)
			d_q *= -1;
		if (str[i] == '\'' && d_q != -1)
			s_q *= -1;
		if ((str[i] == ';' || str[i] == '|') && (s_q != 1 || d_q != 1))
		{
			tmp = str[i];
			i = ft_skip_spaces(str, ++i);
			if (tmp == ';' && (str[i] == '|' || str[i] == ';'))
				return (ft_print_stntax_error(strct, str[i]));
			else if (tmp == '|' && str[i] == ';')
				return (ft_print_stntax_error(strct, str[i]));
		}
		if ((str[i] == '>' || str[i] == '<') && (s_q != 1 || d_q != 1))
		{
			if (str[++i] == '>')
				i++;
			i = ft_skip_spaces(str, i);
			if (!str[i] || str[i] == ';' || str[i] == '|')
				return (ft_print_stntax_error(strct, str[i]));
		}
		i++;
	}
	return (0);
}
