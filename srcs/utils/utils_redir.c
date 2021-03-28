/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 19:07:10 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 17:25:24 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void		work_if_head_null(t_redirect **redir_head, \
		t_args **cur_t_arg, char *type)
{
	if (((*redir_head) = (t_redirect *)malloc(sizeof(t_redirect))) == NULL)
		ft_write_malloc_error();
	(*redir_head)->type = ft_strdup_new(type);
	(*redir_head)->file_name = NULL;
	(*redir_head)->next = NULL;
	(*cur_t_arg)->redir_head = (*redir_head);
	(*cur_t_arg)->redir_flag = 1;
	if (!ft_strncmp((*redir_head)->type, "<", 1))
		(*cur_t_arg)->left_redir += 1;
	else if (!ft_strncmp((*redir_head)->type, ">", 1))
		(*cur_t_arg)->right_redir += 1;
}

static	t_redirect	*get_last_env_list(t_redirect *head)
{
	t_redirect *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

static	void		add_file_name(t_redirect *tmp, t_args **cur_t_arg, \
		char *file_name)
{
	tmp->file_name = ft_strdup_new(file_name);
	(*cur_t_arg)->redir_flag = 0;
}

void				ft_push_back_redir_list(t_args **cur_t_arg, \
		t_redirect *redir_head, char *type, char *file_name)
{
	t_redirect *tmp;
	t_redirect *new;

	if (redir_head == NULL)
		return (work_if_head_null(&redir_head, cur_t_arg, type));
	tmp = get_last_env_list(redir_head);
	if (tmp->type != NULL && tmp->file_name == NULL)
		return (add_file_name(tmp, cur_t_arg, file_name));
	if ((new = (t_redirect *)malloc(sizeof(t_redirect))) == NULL)
		ft_write_malloc_error();
	new->type = ft_strdup_new(type);
	new->file_name = NULL;
	new->next = NULL;
	tmp->next = new;
	(*cur_t_arg)->redir_flag = 1;
	if (!ft_strncmp(new->type, "<", 1))
		(*cur_t_arg)->left_redir += 1;
	else if (!ft_strncmp(new->type, ">", 1))
		(*cur_t_arg)->right_redir += 1;
}

void				ft_free_redir(t_redirect *head)
{
	t_redirect *tmp;

	tmp = head;
	while (tmp)
	{
		free(tmp->type);
		free(tmp->file_name);
		head = head->next;
		free(tmp);
		tmp = head;
	}
}
