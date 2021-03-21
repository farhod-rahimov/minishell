/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:52:30 by btammara          #+#    #+#             */
/*   Updated: 2021/03/21 10:16:59 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_parse(t_struct *strct, t_args *tmp_head, int i)
{
	t_args	*tmp;

	tmp = tmp_head;
		
	while (strct->parsed_str[i])
	{
		while (strct->parsed_str[i] == ' ')
			i++;
		if (strct->parsed_str[i] == ';' || strct->parsed_str[i] == '|')				// str cannot start with ; | 
			return (-1);
		else if ((strct->parsed_str[i] == '<' || strct->parsed_str[i] == '>') && tmp_head->arg)
			return (-1);
		else if (strct->parsed_str[i] == '\"')
			i = ft_parse_str_till_dq_ends(&tmp, ++i, strct, 1);						// dq = double quotes // ++i for skipping the first "
		else if (strct->parsed_str[i] == '\'')
			i = ft_parse_str_till_sq_ends(&tmp, ++i, strct, 1);						// sq = single quote // ++i for skipping the first '
		else if (strct->parsed_str[i] == '$' && (ft_isalnum(strct->parsed_str[i + 1]) || strct->parsed_str[i + 1] == '_'))
			i = ft_parse_str_till_env_var_ends(&tmp, ++i, strct, 1);
		else if (strct->parsed_str[i] == '$' && (!ft_isalnum(strct->parsed_str[i + 1]) && strct->parsed_str[i + 1] != '_'))
			i = ft_work_with_dollar(&tmp, ++i, strct);
		// else if (strct->parsed_str[i] == '|')
		// 	ft_work_with_pipe;
		// else if (strct->parsed_str[i] == '>')
		// 	ft_work_with_right_redirect;
		// else if (strct->parsed_str[i] == '<')
		// 	ft_work_with_left_redirect;
		else
			i = ft_parse_str_till_it_ends(&tmp, i, strct, 1);
	}
	free(strct->parsed_str);
	return (0);
}

void	ft_print_devided_args(t_args *head)
{
	t_args	*tmp;
	int		i;
	int		k;

	tmp = head;
	i = 0;
	k = 0;
	printf("------------------------\n");
	while (tmp)
	{
		while (tmp->arg[i])
		{
			printf("arg[%d][%d]	|%s|\n", k, i, tmp->arg[i]);
			i++;
		}
		printf("arg[%d][pipe]	|%d|\n", k, tmp->pipe);
		printf("arg[%d][s_lh]	|%d|\n", k, tmp->s_lh_redirect);
		printf("arg[%d][s_rh]	|%d|\n", k, tmp->s_rh_redirect);
		printf("arg[%d][d_rh]	|%d|\n", k, tmp->d_rh_redirect);
		printf("------------------------\n\n");
		i = 0;
		k++;
		tmp = tmp->next;
	}
}
