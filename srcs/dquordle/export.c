/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:38:19 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:38:20 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_rewrite(t_env *head, char *key, char *value)
{
	t_env *tmp;

	tmp = head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (value)
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = ft_strdup_new(value);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			ft_add_env(t_env **head, char *arg)
{
	char	*value;
	int		i;
	int		found;

	if (!valid(arg))
		return (1);
	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	value = NULL;
	if (arg[i])
		value = arg + i + 1;
	arg[i] = 0;
	found = 0;
	if (*head)
		found = ft_rewrite(*head, arg, value);
	if (!found)
		ft_new_env(head, arg, value);
	return (0);
}

static void	ft_sort_arr(char **array)
{
	int		i;
	int		flag;
	char	*tmp;

	flag = 1;
	while (flag != 0)
	{
		flag = 0;
		i = 0;
		while (array[i + 1])
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				flag++;
			}
			i++;
		}
	}
}

static char	**ft_sp_to_arr(t_env *env_head)
{
	int		i;
	char	**env;
	t_env	*tmp;

	tmp = env_head;
	i = ft_get_size_env(tmp);
	if ((env = (char **)malloc(sizeof(char *) * i)) == NULL)
		ft_write_malloc_error();
	i = -1;
	while (tmp)
	{
		env[++i] = ft_strdup_new("declare -x ");
		env[i] = ft_append(env[i], tmp->key);
		if (tmp->value)
		{
			env[i] = ft_append(env[i], "=\"");
			env[i] = ft_append(env[i], tmp->value);
			env[i] = ft_append(env[i], "\"");
		}
		env[i] = ft_append(env[i], "\n");
		tmp = tmp->next;
	}
	env[++i] = NULL;
	ft_sort_arr(env);
	return (env);
}

void		ft_export(char **arg, t_env **head, int *exit_value)
{
	int		i;
	char	**env;

	if (*head && !arg[1])
	{
		env = ft_sp_to_arr(*head);
		i = -1;
		while (env[++i])
			write(1, env[i], ft_strlen(env[i]));
		i = 0;
		while (env[i])
			free(env[i++]);
		free(env);
		*exit_value = 0;
	}
	else
	{
		i = 1;
		while (arg[i])
			*exit_value += ft_add_env(head, arg[i++]);
	}
	if (*exit_value)
		*exit_value = 1;
}
