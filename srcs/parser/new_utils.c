/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:08:30 by btammara          #+#    #+#             */
/*   Updated: 2021/03/18 10:32:38 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_if_new_list_or_arg_is_needed(t_struct *strct, t_args **current_t_arg, int i)
{
    int len;
    
    if (i >= (len = ft_strlen(strct->parsed_str)))
        return (len);
	if (strct->parsed_str[i] == ' ')
		strct->n_i++;
	while (strct->parsed_str[i] == ' ')
		i++;
	if (strct->parsed_str[i] == ';')
	{
		i++;
		if ((*current_t_arg = ft_create_new_t_args(strct, *current_t_arg)) == NULL)
			return (-1);
	}
	return (i);
}

int		ft_copy_str_to_structure_t_args(t_args **tmp, char *str, int n_i) //rewrite
{
	char	**tmp_arg; // tmp->arg
	
	tmp_arg = (*tmp)->arg;
	if (tmp_arg == NULL)
	{
		if (((*tmp)->arg = (char **)malloc(sizeof(char *) * 2)) == NULL)
			ft_error();
		if (((*tmp)->arg[0] = ft_strdup(str)) == NULL)
			ft_error();
		if (((*tmp)->arg[1] = ft_strdup("")) == NULL)
			ft_error();
		return (0);
	}
	if (((*tmp)->arg = (char **)malloc(sizeof(char *) * (n_i + 2))) == NULL)
		ft_error();
	ft_copy_old_arg_to_new(tmp, tmp_arg, n_i);
	if (((*tmp)->arg[n_i] = ft_strjoin(tmp_arg[n_i], str)) == NULL)
		ft_error();
	if (((*tmp)->arg[n_i + 1] = ft_strdup("")) == NULL)
		ft_error();

	ft_free_arg(tmp_arg);
	return (0);
}

void		ft_push_back_char(char **str, char c)
{
	int		len;
	char	*tmp;
	
	len = ft_strlen(*str);
	tmp = *str;
	if ((*str = (char *)malloc(sizeof(char) * (len + 2))) == NULL)
		ft_error();
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
		if (((*new_arg)->arg[i] = ft_strdup(old_arg[i])) == NULL)
			ft_error();
		i++;
	}
	return (0);
}

void	ft_free_arg(char **tmp_arg)
{
	int i;

	i = 0;
	while (tmp_arg[i][0])
	{
		free(tmp_arg[i++]);
	}
	free(tmp_arg[i]);
	free(tmp_arg);
}