/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:08:30 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 15:10:12 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_tolower_str(char *str);

t_args	*ft_create_new_t_args(t_struct *strct, t_args *prev_t_args)
{
	t_args *new_t_args;

	if ((new_t_args = (t_args *)malloc(sizeof(t_args))) == NULL)
		ft_write_malloc_error();
	new_t_args->next = NULL;
	new_t_args->prev = NULL;
	new_t_args->arg = NULL;
	new_t_args->redir_head = NULL;

	new_t_args->pipe = 0;
	new_t_args->right_redir = 0;
	new_t_args->left_redir = 0;
	new_t_args->redir_flag = 0;
	new_t_args->exec_done = 0;
		
	if (prev_t_args != NULL)
	{
		prev_t_args->next = new_t_args;
		new_t_args->prev = prev_t_args;
	}

	strct->n_i = 0;
	
	return (new_t_args);
}

int ft_check_if_new_list_or_arg_is_needed(t_struct *strct, t_args **current_t_arg, int i)
{
    int len;
    
    if (i >= (len = ft_strlen(strct->parsed_str)))
        return (len);
	if (strct->parsed_str[i] == ' ')
		strct->n_i++;
	i = ft_skip_spaces(strct->parsed_str, i);
	if (strct->parsed_str[i] == ';' || strct->parsed_str[i] == '|')
	{
		if (strct->parsed_str[i] == ';')
		{
			// ft_print_devided_args(*current_t_arg);
			ft_work_with_t_arg_lists(strct, current_t_arg);
		}
		if (strct->parsed_str[i] == '|')
		{
			if ((*current_t_arg)->prev)
			{
				if ((*current_t_arg)->prev->pipe)
					(*current_t_arg)->pipe += (*current_t_arg)->prev->pipe + 1;
				else
					(*current_t_arg)->pipe = 1;
			}
			else
				(*current_t_arg)->pipe = 1;
		}
		i = ft_skip_spaces(strct->parsed_str, ++i);
		if (strct->parsed_str[i] != '\0')
			*current_t_arg = ft_create_new_t_args(strct, *current_t_arg);
	}
	else if (strct->parsed_str[i] == '>' || strct->parsed_str[i] == '<')
	{
		if (strct->parsed_str[i] == '>' && strct->parsed_str[i + 1] == '>')
		{
			i++;
			ft_push_back_redir_list(current_t_arg, (*current_t_arg)->redir_head, ">>", NULL);
		}
		else if (strct->parsed_str[i] == '>')
			ft_push_back_redir_list(current_t_arg, (*current_t_arg)->redir_head, ">", NULL);
		else if (strct->parsed_str[i] == '<')
			ft_push_back_redir_list(current_t_arg, (*current_t_arg)->redir_head, "<", NULL);
		i++;
	}
	return (i);
}

void		ft_push_back_redir_list(t_args **current_t_arg, t_redirect *redir_head, char *type, char *file_name)
{
	t_redirect *tmp;
	t_redirect *new;

	if (redir_head == NULL)
	{
		if ((redir_head = (t_redirect *)malloc(sizeof(t_redirect))) == NULL)
			ft_write_malloc_error();
		redir_head->type = ft_strdup_new(type);
		redir_head->file_name = NULL;
		redir_head->next = NULL;
		(*current_t_arg)->redir_head = redir_head;
		(*current_t_arg)->redir_flag = 1;
		return ;
	}
	tmp = redir_head;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	
	if (tmp->type != NULL && tmp->file_name == NULL)
	{
		tmp->file_name = ft_strdup_new(file_name);
		if (!ft_strncmp(tmp->type, "<", 1))
			(*current_t_arg)->left_redir += 1;
		else if (!ft_strncmp(tmp->type, ">", 1))
			(*current_t_arg)->right_redir += 1;
		(*current_t_arg)->redir_flag = 0;
		return ;
	}

	if ((new = (t_redirect *)malloc(sizeof(t_redirect))) == NULL)
		ft_write_malloc_error();
	new->type = ft_strdup_new(type);
	new->file_name = NULL;
	new->next = NULL;
	tmp->next = new;
	(*current_t_arg)->redir_flag = 1;
}

void		ft_copy_str_to_structure_t_args(t_struct *strct, t_args **tmp, char *str, int n_i)
{
	char	**tmp_arg; // tmp->arg
	
	tmp_arg = (*tmp)->arg;

	if ((*tmp)->redir_flag)
	{
		ft_push_back_redir_list(tmp, (*tmp)->redir_head, NULL, str);
		strct->n_i -= 1;
		return ;
	}
	if (tmp_arg == NULL)
	{
		if (((*tmp)->arg = (char **)malloc(sizeof(char *) * 2)) == NULL)
			ft_write_malloc_error();
		(*tmp)->arg[0] = ft_strdup_new(str);
		(*tmp)->arg[1] = NULL;
		return ;
	}
	ft_tolower_str((*tmp)->arg[0]);
	if (((*tmp)->arg = (char **)malloc(sizeof(char *) * (n_i + 2))) == NULL)
		ft_write_malloc_error();
	ft_copy_old_arg_to_new(tmp, tmp_arg, n_i);
	(*tmp)->arg[n_i] = ft_strjoin_new(tmp_arg[n_i], str);
	(*tmp)->arg[n_i + 1] = NULL;
	ft_free_arg(tmp_arg);
}

static	void	ft_tolower_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

void		ft_push_back_char(char **str, char c)
{
	int		len;
	char	*tmp;
	
	len = ft_strlen(*str);
	tmp = *str;
	if ((*str = (char *)malloc(sizeof(char) * (len + 2))) == NULL)
		ft_write_malloc_error();
	ft_strcopy(*str, tmp);
	(*str)[len] = c;
	(*str)[len + 1] = '\0';
	free(tmp);
	return ;
}

void	ft_error()
{
	write(1, "malloc error\n", ft_strlen("malloc error\n"));
	exit(1);
}

void	ft_new_error(t_struct *strct, int i, int exit_flag)
{
	strct->exit_value = i;
	if (exit_flag)
		exit(i);
}

void	ft_dup2_error(t_struct *strct)
{
	char *error;

	error = "dup2 error\n";
	strct->exit_value = 1;
	write(2, "my_bash: ", 9);
	write(2, error, ft_strlen(error));
	dup2(strct->initial_fd[0], 0);
	dup2(strct->initial_fd[1], 1);
	exit(1);
}

void	ft_errno_error(t_struct *strct, char *file_name)
{
	strct->exit_value = 1;
	write(2, "my_bash: ", 9);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(1);
}

void	ft_write_malloc_error(void)
{
	printf("here\n");
	write(2, "my_bash: ", 9);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(1);
}

void	ft_strcopy(char *dst, char *src)
{
	int i;
	int max;

	i = 0;
	max = ft_strlen(src);
	while (i < max)
	{
		dst[i] = src[i];
		i++;
	}
}

int		ft_copy_old_arg_to_new(t_args **new_arg, char **old_arg, int n_i)
{
	int		i;

	i = 0;
	while (i < n_i)
	{
		(*new_arg)->arg[i] = ft_strdup_new(old_arg[i]);
		i++;
	}
	return (0);
}

void	ft_free_arg(char **tmp_arg)
{
	int i;

	i = 0;
	while (tmp_arg[i])
		free(tmp_arg[i++]);
	// free(tmp_arg[i]);
	free(tmp_arg);
}

void	ft_free_redir(t_redirect *head)
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