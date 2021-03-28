/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:25:46 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 13:22:05 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_devided_args(t_args *head)
{
	t_args		*tmp;
	t_redirect	*tmp_red;
	int		i;
	int		k;

	tmp = head;
	i = 0;
	k = 0;
	printf("------------------------\n");
	while (tmp)
	{
		tmp_red = tmp->redir_head;
		while (tmp->arg && tmp->arg[i])
		{
			printf("arg[%d][%d]	|%s|\n", k, i, tmp->arg[i]);
			i++;
		}
		while (tmp_red)
		{
			printf("arg[%d][type]	|%s|\n", k, tmp_red->type);
			printf("arg[%d][name]	|%s|\n", k, tmp_red->file_name);
			tmp_red = tmp_red->next;
		}
		if (tmp)
		{
			printf("arg[%d][pipe]	|%d|\n", k, tmp->pipe);
			printf("arg[%d][rh_red]	|%d|\n", k, tmp->right_redir);
			printf("arg[%d][lh_red]	|%d|\n", k, tmp->left_redir);
			printf("------------------------\n\n");
		}
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