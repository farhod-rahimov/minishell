/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:39:13 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:39:15 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_del_one(t_env *head)
{
	t_env	*tmp;

	tmp = head->next;
	head->next = tmp->next;
	free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

static void	ft_del_head(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	*head = (*head)->next;
	free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

static int	valid_key(char *str, int *exit_value)
{
	int i;
	int err;

	err = 0;
	if (ft_isdigit(str[0]) || str[0] == 0)
		err++;
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			err++;
		i++;
	}
	if (err)
	{
		write(2, "unset: `", 8);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 26);
		*exit_value = 1;
		return (0);
	}
	return (1);
}

void		ft_unset(char **arg, t_env **head, int *exit_value)
{
	t_env	*tmp;
	int		i;

	*exit_value = 0;
	i = 0;
	while (arg[++i])
	{
		if (!valid_key(arg[i], exit_value))
			continue ;
		tmp = *head;
		if (!ft_strcmp(tmp->key, arg[i]))
			ft_del_head(head);
		else
		{
			while (tmp && tmp->next)
			{
				if (!ft_strcmp(tmp->next->key, arg[i]))
					ft_del_one(tmp);
				tmp = tmp->next;
			}
		}
	}
}
