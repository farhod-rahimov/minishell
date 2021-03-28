/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:38:00 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:38:03 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_env(char **arg, t_env *head, int *exit_value)
{
	t_env	*tmp;
	char	*str;

	tmp = head;
	if (arg[1])
	{
		*exit_value = 2;
		return ;
	}
	while (tmp)
	{
		if (tmp->value)
		{
			str = ft_strdup_new(tmp->key);
			str = ft_append(str, "=");
			str = ft_append(str, tmp->value);
			str = ft_append(str, "\n");
			write(1, str, ft_strlen(str));
			free(str);
		}
		tmp = tmp->next;
	}
	*exit_value = 0;
}

static void	ft_change_pwds(t_env **head, char *old_pwd, int *exit_value)
{
	char *new_pwd;
	char *buf;

	buf = ft_strjoin_new("OLDPWD=", old_pwd);
	ft_add_env(head, buf);
	free(buf);
	new_pwd = NULL;
	new_pwd = getcwd(new_pwd, 0);
	buf = ft_strjoin_new("PWD=", new_pwd);
	ft_add_env(head, buf);
	free(buf);
	free(new_pwd);
	free(old_pwd);
	*exit_value = 0;
}

static void	ft_cd_home(t_env **head, int *exit_value, char *old_pwd)
{
	t_env *tmp;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
		{
			if ((tmp->value)[0] && chdir(tmp->value) == -1)
			{
				write(2, "my_bash: cd: ", 13);
				write(2, tmp->value, ft_strlen(tmp->value));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				*exit_value = 1;
			}
			ft_change_pwds(head, old_pwd, exit_value);
			return ;
		}
		tmp = tmp->next;
	}
	write(2, "my_bash: cd: HOME not set\n", 26);
	*exit_value = 1;
}

void		ft_cd(char **arg, t_env **head, int *exit_value)
{
	char *old_pwd;

	old_pwd = NULL;
	old_pwd = getcwd(old_pwd, 0);
	if (!arg[1])
		ft_cd_home(head, exit_value, old_pwd);
	else if (arg[1][0] && chdir(arg[1]) == -1)
	{
		write(2, "my_bash: cd: ", 13);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		free(old_pwd);
		*exit_value = 1;
	}
	else
		ft_change_pwds(head, old_pwd, exit_value);
}
