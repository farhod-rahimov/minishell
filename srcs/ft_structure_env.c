/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structure_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:21:41 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 09:30:56 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static	void	ft_add_slash_to_the_end_of_each_path_to_bins(t_struct *strct);

int	ft_structure_env(t_struct *strct, char **env)
{
	t_env *tmp;
	t_env *prev;
	int i;
	int k;
	
	if ((strct->env_head = (t_env *)malloc(sizeof(t_env))) == NULL)
		return (-1);
	tmp = strct->env_head;
	tmp->next = NULL;
	i = 0;
	while (env[i])
	{
		k = 0;
		if (i > 0)
			if ((tmp = ft_create_new_t_env(prev)) == NULL)
				return (-1);
		while (env[i][k] != '=' && env[i][k] != '\0')
			k++;
		ft_fill_t_env_list(tmp, env, i, k);
		prev = tmp;
		i++;
	}


	ft_get_path_to_bins(strct);
	ft_change_shell_level(strct->env_head); /// это при запуске нашего минишелла
	
	// ft_print_env(strct->env_head);
	return (0);
}

void	ft_fill_t_env_list(t_env *env_list, char **env, int i, int k)
{
	env_list->key = ft_substr(env[i], 0, k);
	if (env[i][k] == '=')
		env_list->value = ft_substr(env[i], ++k, ft_strlen(env[i]));
	else
		env_list->value = NULL;
}

t_env	*ft_create_new_t_env(t_env *prev)
{
	t_env *new;
	
	if ((new = (t_env *)malloc(sizeof(t_env))) == NULL)
			return (NULL);
	prev->next = new;	
	new->next = NULL;
	return (new);
}

void	ft_get_path_to_bins(t_struct *strct)
{
	t_env *tmp;

	strct->path_to_bins = NULL;
	tmp = strct->env_head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)) == 0)
		{
			strct->path_to_bins = ft_split(tmp->value, ':');
			ft_add_slash_to_the_end_of_each_path_to_bins(strct);
		}
		tmp = tmp->next;
	}
	// ft_print_path_to_bins(strct->path_to_bins);
}

static	void	ft_add_slash_to_the_end_of_each_path_to_bins(t_struct *strct)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strct->path_to_bins[i])
	{
		tmp = strct->path_to_bins[i];
		strct->path_to_bins[i++] = ft_strjoin(tmp, "/");
		free(tmp);
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

// no NULL 
