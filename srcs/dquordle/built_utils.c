/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:37:30 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:37:32 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		valid(char *str)
{
	int i;
	int err;

	err = 0;
	if (ft_isdigit(str[0]) || str[0] == 0)
		err++;
	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			err++;
		i++;
	}
	if (err)
	{
		write(2, "export: `", 9);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 26);
		return (0);
	}
	return (1);
}

int		ft_get_size_env(t_env *tmp)
{
	int i;

	i = 1;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_new_env(t_env **head, char *key, char *value)
{
	t_env	*new_env;
	t_env	*tmp;

	if ((new_env = (t_env *)malloc(sizeof(t_env))) == NULL)
		ft_write_malloc_error();
	new_env->next = NULL;
	new_env->key = ft_strdup_new(key);
	new_env->value = NULL;
	if (value)
		new_env->value = ft_strdup_new(value);
	if (!(*head))
		*head = new_env;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}
