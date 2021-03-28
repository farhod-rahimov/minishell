/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:25:46 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 10:16:25 by btammara         ###   ########.fr       */
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
		// printf("arg[%d][ex_uns]	|%s|\n", k, tmp->arg_exp_uns);
		printf("arg[%d][rh_red]	|%d|\n", k, tmp->right_redir);
		printf("arg[%d][lh_red]	|%d|\n", k, tmp->left_redir);
		printf("------------------------\n\n");
		i = 0;
		k++;
		tmp = tmp->next;
	}
}

void	ft_print_env(t_env *head)
{
	t_env *tmp;
	
	tmp = head;
	while (tmp)
	{
		printf("%s", tmp->key);
		printf("=%s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	ft_print_path_to_bins(char **path_to_bins)
{
	if (!path_to_bins)
		return;
	int i = 0;
	while (path_to_bins[i])
		printf("%s\n", path_to_bins[i++]);
}