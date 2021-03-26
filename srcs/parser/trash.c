/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:25:46 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 17:25:53 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
