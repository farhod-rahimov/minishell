/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_dq_ends.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:56:32 by btammara          #+#    #+#             */
/*   Updated: 2021/03/16 14:55:18 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int		ft_check_spec_symb_in_dq(t_struct *strct);
static	int		ft_work_with_env_var_in_dq(t_env *env_head, t_args **tmp_args, int i, int n_i);
static	char	*ft_get_env_var_value(t_env *env_head, char **env_var);

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
                if ((i = ft_work_with_env_var_in_dq(strct->env_head, &tmp, i + 1, strct->n_i - 1)) == -1)
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

static	int		ft_work_with_env_var_in_dq(t_env *env_head, t_args **tmp_args, int i, int n_i)
{
	char	*env_var;
	char	*tmp1;
	char	*tmp2;
    int		initial_i;
	
	initial_i = i;
    if (i > 1)  // first char of the (*tmp_args)->arg[n_i] is 0, but in this function it comes as 1 ($ skipped)
        if ((*tmp_args)->arg[n_i][i - 2] == '\\')
            return (i);
    if ((*tmp_args)->arg[n_i][i] == ' ' && (*tmp_args)->arg[n_i][i] == '\0')
        return (i);

	while ((*tmp_args)->arg[n_i][i] && (*tmp_args)->arg[n_i][i] != ' ' && (*tmp_args)->arg[n_i][i] != '$' && (*tmp_args)->arg[n_i][i] != '\'' && (*tmp_args)->arg[n_i][i] != '\"')
		i++;
	if ((env_var = ft_substr((*tmp_args)->arg[n_i], initial_i, i - initial_i)) == NULL)
		return (-1);
	if ((env_var = ft_get_env_var_value(env_head, &env_var)) == NULL)
		return (-1);

	tmp1 = ft_strdup((*tmp_args)->arg[n_i]);
	tmp1[initial_i - 1] = '\0';

	tmp2 = (*tmp_args)->arg[n_i];
	(*tmp_args)->arg[n_i] = ft_strjoin(tmp1, env_var);
	free(tmp2);
	free(env_var);

	tmp2 = (*tmp_args)->arg[n_i];
	(*tmp_args)->arg[n_i] = ft_strjoin((*tmp_args)->arg[n_i], tmp1 + i);
	free(tmp1);
	free(tmp2);

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