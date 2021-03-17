/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_dq_ends.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:56:32 by btammara          #+#    #+#             */
/*   Updated: 2021/03/17 09:24:39 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// нужно ли обрабатывать такое echo "$(PWD)"
//echo * \* "*" '*'
//ls * "*"
//echo "$" "\$" echo "$""\$" где записать пробел

static	int		ft_check_spec_symb_in_dq(t_struct *strct);
static	int		ft_work_with_env_var_in_dq(t_struct *strct, t_args **tmp_args, int i, int n_i);
static	char	*ft_get_env_var_value(t_env *env_head, char **env_var);
static	int		ft_check_and_work_with_backslash(t_args **args, int i, int n_i);
static	void	ft_replace_some_var_in_str_to_its_value(t_struct *strct, char **env_var, int i, int initial_i);
static	int		ft_work_with_return_value(t_struct *strct, int i);

int		ft_parse_str_till_dq_ends(t_args **current_t_arg, int i, t_struct *strct, int k)
{
	char	*str;
	
	if ((str = (char *)malloc(sizeof(char) * (k + 1))) == NULL)
		return (-1);
	
	while (strct->parsed_str[i] && strct->parsed_str[i] != '\"')
	{
		if ((str = ft_add_back_str(str, k++, strct->parsed_str[i])) == NULL)
			return (-1);
		i++;
	}

	if ((ft_copy_str_to_structure_args(*current_t_arg, str, strct->n_i++)) == -1)	// n_i++
		return (-1); //malloc error
	free(str);

	if (ft_check_spec_symb_in_dq(strct) == -1)
		return (-1);
	i = ft_check_if_new_list_is_needed(strct, current_t_arg, ++i); // ++i for skipping the last '
	return (i);
}

static	int		ft_check_spec_symb_in_dq(t_struct *strct)
{
	t_args	*tmp;
	int		i;

	tmp = strct->args_head;
	i = 0;
	while (tmp)
	{
		while (tmp->arg[strct->n_i - 1][i])
		{
			if (tmp->arg[strct->n_i - 1][i] == '$')
			{
				if (tmp->arg[strct->n_i - 1][i + 1] == '?' && tmp->arg[strct->n_i - 1][i - 1] != '\\')
				{
					if ((i = ft_work_with_return_value(strct, ++i)) == -1)
						return (-1);
				}
                else if ((i = ft_work_with_env_var_in_dq(strct, &tmp, i + 1, strct->n_i - 1)) == -1)
                    return (-1);
			}
			else
				i++;
		}
		i = 0;
		tmp = tmp->next;	
	}
	return (0);
}

static int ft_work_with_return_value(t_struct *strct, int i)
{
	int		return_value = 5678; // change
	char	*ret_val;

	if ((ret_val = ft_itoa(return_value)) == NULL)
		return (-1);
	
	ft_replace_some_var_in_str_to_its_value(strct, &ret_val, i + 1, i);
	return (++i);
}
static	int		ft_work_with_env_var_in_dq(t_struct *strct, t_args **tmp_args, int i, int n_i)
{
	char	*env_var;
    int		initial_i;
	
	initial_i = i;
    if (i > 1)  // first char of the (*tmp_args)->arg[n_i] is 0, but in this function it comes as 1 ($ skipped)
		if ((i = ft_check_and_work_with_backslash(tmp_args, i, n_i)) != initial_i)
			return (i);

    if ((*tmp_args)->arg[n_i][i] == ' ' || (*tmp_args)->arg[n_i][i] == '\0' || (*tmp_args)->arg[n_i][i] == '$')
        return (i + 1);

	while ((*tmp_args)->arg[n_i][i] && (*tmp_args)->arg[n_i][i] != ' ' && (*tmp_args)->arg[n_i][i] != '$' && (*tmp_args)->arg[n_i][i] != '\'' && (*tmp_args)->arg[n_i][i] != '\"')
		i++;
	if ((env_var = ft_substr((*tmp_args)->arg[n_i], initial_i, i - initial_i)) == NULL)
		return (-1);
	if ((env_var = ft_get_env_var_value(strct->env_head, &env_var)) == NULL)
		return (-1);

	ft_replace_some_var_in_str_to_its_value(strct, &env_var, i, initial_i);
	return (i);
}

static	void	ft_replace_some_var_in_str_to_its_value(t_struct *strct, char **env_var, int i, int initial_i)
{
	char	*tmp1;
	char	*tmp2;
	t_args	*args;
	
	args = strct->args_head;

	tmp1 = ft_strdup(args->arg[strct->n_i - 1]);
	tmp1[initial_i - 1] = '\0';

	tmp2 = args->arg[strct->n_i - 1];
	args->arg[strct->n_i - 1] = ft_strjoin(tmp1, *env_var);
	free(tmp2);
	free(*env_var);

	tmp2 = args->arg[strct->n_i - 1];
	args->arg[strct->n_i - 1] = ft_strjoin(args->arg[strct->n_i - 1], tmp1 + i);
	free(tmp1);
	free(tmp2);
}

static	int		ft_check_and_work_with_backslash(t_args **args, int i, int n_i)
{
	char	*tmp1;
	char	*tmp2;
	
	if ((*args)->arg[n_i][i - 2] == '\\')
	{
		tmp1 = ft_strdup((*args)->arg[n_i]);
		tmp1[i - 2] = '\0';

		tmp2 = (*args)->arg[n_i];
		(*args)->arg[n_i] = ft_substr(tmp2, i - 1, ft_strlen(tmp2));
		free(tmp2);

		tmp2 = (*args)->arg[n_i];
		(*args)->arg[n_i] = ft_strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
		return (i - 1); // i - 1 because we removed '\' before $, now ft_strlen(tmp_args->arg[n_i]) -= 1 
	}
	return (i);
}

static	char	*ft_get_env_var_value(t_env *env_head, char **env_var)
{
	t_env *tmp;

	tmp = env_head;
	while (tmp)
	{
		if (ft_strncmp(*env_var, tmp->key, ft_strlen(*env_var) + ft_strlen(tmp->value)) == 0)
		{
			free(*env_var);
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	free(*env_var);
	return (ft_strdup(""));
}