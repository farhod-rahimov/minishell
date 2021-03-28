/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:09:39 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 19:51:05 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*ft_str_from_char(char c)
{
	char	*str;

	if ((str = (char *)malloc(sizeof(char) * 2)) == NULL)
		ft_write_malloc_error();
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static	int		part1(t_struct *strct, int i, int *s_q, int *d_q)
{
	char	tmp;
	char	*str;

	str = strct->parsed_str;
	if (str[i] == '|')
	{
		i = ft_skip_spaces(str, ++i);
		if (str[i] == '|' || str[i] == ';' || str[i] == '<' || str[i] == '>')
			return (ft_print_syntax_error(strct, str[i]));
	}
	if ((str[i] == ';' || str[i] == '|') && (*s_q != 1 || *d_q != 1))
	{
		tmp = str[i];
		i = ft_skip_spaces(str, ++i);
		if (tmp == ';' && (str[i] == '|' || str[i] == ';'))
			return (ft_print_syntax_error(strct, str[i]));
		else if (tmp == '|' && str[i] == ';')
			return (ft_print_syntax_error(strct, str[i]));
	}
	return (i);
}

static	int		part2(t_struct *strct, int i)
{
	int		tmp_i;
	char	*s;

	s = strct->parsed_str;
	if (s[i] == '>' && s[i + 1] == '>')
	{
		i += 2;
		i = ft_skip_spaces(s, i);
		if (s[i] == '>' || s[i] == '<' || s[i] == '|' || s[i] == ';')
			return (ft_print_syntax_error(strct, s[i]));
	}
	if ((s[i] == '>' && s[i + 1] == '>' && s[i + 2] == ' ') || \
	(s[i] == '>' && s[i + 1] == ' ') || (s[i] == '<' && s[i + 1] == ' '))
	{
		tmp_i = i;
		tmp_i = ft_skip_spaces(s, ++tmp_i);
		if (i != tmp_i && (s[tmp_i] == '>' || s[tmp_i] == '<' || \
		s[tmp_i] == '|' || s[tmp_i] == ';'))
			return (ft_print_syntax_error(strct, s[i]));
	}
	return (i);
}

static	int		part3(t_struct *strct, int i, int *s_q, int *d_q)
{
	char	*str;

	str = strct->parsed_str;
	if ((str[i] == '>' || str[i] == '<') && (*s_q != 1 || *d_q != 1))
	{
		if (str[++i] == '>')
			i++;
		i = ft_skip_spaces(str, i);
		if (!str[i] || str[i] == ';' || str[i] == '|')
			return (ft_print_syntax_error(strct, str[i]));
	}
	return (i);
}

int				ft_check_syntax(t_struct *strct, char *str, int s_q, int d_q)
{
	int		i;
	int		first_time;

	i = 0;
	first_time = 0;
	while (str[i])
	{
		i = ft_skip_spaces(str, i);
		if (first_time++ == 0 && (str[i] == '|' || str[i] == ';'))
			return (ft_print_syntax_error(strct, str[i]));
		if (str[i] == '\\')
			i += 2;
		if (str[i] == '"' && s_q != -1)
			d_q *= -1;
		if (str[i] == '\'' && d_q != -1)
			s_q *= -1;
		if ((i = part1(strct, i, &s_q, &d_q)) == -1)
			return (-1);
		if ((i = part2(strct, i)) == -1)
			return (-1);
		if ((i = part3(strct, i, &s_q, &d_q)) == -1)
			return (-1);
		i++;
	}
	return (0);
}
