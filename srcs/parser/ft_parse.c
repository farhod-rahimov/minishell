/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:52:30 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 15:24:05 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_parse(t_struct *strct, t_args *tmp_head, int i)
{
	t_args	*tmp;

	// if ((strct->output_fd = open(OUTPUT, O_CREAT | O_TRUNC | O_WRONLY, 0766)) == -1)
	// 	write (2, "cannot create a new file to record the result of minishell operation\n", 69);
	// dup2(strct->output_fd, 1);
	tmp = tmp_head;

	if (ft_check_syntax(strct, strct->parsed_str) == -1)
		return (-1);
	while (strct->parsed_str[i])
	{
		while (strct->parsed_str[i] == ' ')
			i++;
		// if (strct->parsed_str[i] == ';' || strct->parsed_str[i] == '|')				// str cannot start with ; | 
		// {
		// 	// free(strct->parsed_str);
		// 	write(2, "syntax error\n", 13);
		// 	free(strct->args_head);
		// 	strct->args_head = NULL;
		// 	// dup2(strct->initial_fd[1], 1);
		// 	return (-1);
		// }
			
		// else if ((strct->parsed_str[i] == '<' || strct->parsed_str[i] == '>') && tmp_head->arg)
		// 	return (-1);
		if (strct->parsed_str[i] == '\"')
			i = ft_parse_str_till_dq_ends(&tmp, ++i, strct);						// dq = double quotes // ++i for skipping the first "
		else if (strct->parsed_str[i] == '\'')
			i = ft_parse_str_till_sq_ends(&tmp, ++i, strct);						// sq = single quote // ++i for skipping the first '
		else if (strct->parsed_str[i] == '$' && (ft_isalnum(strct->parsed_str[i + 1]) || strct->parsed_str[i + 1] == '_'))
			i = ft_parse_str_till_env_var_ends(&tmp, ++i, strct);
		else if (strct->parsed_str[i] == '$' && (!ft_isalnum(strct->parsed_str[i + 1]) && strct->parsed_str[i + 1] != '_'))
			i = ft_work_with_dollar(&tmp, ++i, strct);
		// else if (strct->parsed_str[i] == '|')
		// 	ft_work_with_pipe;
		// else if (strct->parsed_str[i] == '>')
		// 	ft_work_with_right_redirect;
		// else if (strct->parsed_str[i] == '<')
		// 	ft_work_with_left_redirect;
		else
			i = ft_parse_str_till_it_ends(&tmp, i, strct);
	}
	free(strct->parsed_str);
	ft_work_with_t_arg_lists(strct, &tmp);
	// dup2(strct->initial_fd[1], 1);
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
		while (tmp->redir_head)
		{
			printf("arg[%d][type]	|%s|\n", k, tmp->redir_head->type);
			printf("arg[%d][name]	|%s|\n", k, tmp->redir_head->file_name);
			tmp->redir_head = tmp->redir_head->next;
		}
		printf("arg[%d][pipe]	|%d|\n", k, tmp->pipe);
		printf("arg[%d][rh_red]	|%d|\n", k, tmp->right_redir);
		printf("arg[%d][lh_red]	|%d|\n", k, tmp->left_redir);
		printf("------------------------\n\n");
		i = 0;
		k++;
		tmp = tmp->next;
	}
}
