/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 19:08:57 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 19:51:05 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_print_syntax_error(t_struct *strct, char c)
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

void	ft_file_error(char *file)
{
	write(2, "my_bash: ", 9);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\nChange name of the history file please\n", 40);
	exit(1);
}

void	ft_term_error(void)
{
	write(2, "my_bash: Set the TERM variable\n", 31);
	exit(1);
}
