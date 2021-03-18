/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_promt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:17:01 by btammara          #+#    #+#             */
/*   Updated: 2021/03/18 09:51:45 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		ft_add_back_string(t_struct *strct, int i, char c);

int	ft_show_prompt(t_struct *strct, int i)
{
	char	c;

	if ((strct->parsed_str = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (-1);

	write(1, "my_bash% ", 9);
	while ((read(0, &c, 1) == 1) && c != '\n') // Количество считываемых символов с инпута ограничено. Разобраться почему это так
	{
		if ((i = ft_add_back_string(strct, i, c)) == -1)
			return (-1);
	}
	
	// printf("parsed str \"%s\"\n", strct->parsed_str);
	
	if (ft_begin_parsing(strct) == -1)
		return (-1);
	return (0);	
}

static	int	ft_add_back_string(t_struct *strct, int i, char c)
{
	char *old_parsed_str;
	
	strct->parsed_str[i - 1] = c;
	strct->parsed_str[i++] = '\0';
	old_parsed_str = strct->parsed_str;
	if ((strct->parsed_str = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (-1);
	ft_copy_old_str(old_parsed_str, strct->parsed_str);
	free(old_parsed_str);
	return (i);
}

int	ft_begin_parsing(t_struct *strct)
{
	if ((strct->args_head = ft_create_new_t_args(strct, NULL)) == NULL)
		return (-1);

	if ((ft_parse(strct, strct->args_head, 0)) == -1)
		return (-1);
	
	ft_print_devided_args(strct->args_head);
	
	return (0);
}