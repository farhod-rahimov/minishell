/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_with_t_arg_lists.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:46:37 by btammara          #+#    #+#             */
/*   Updated: 2021/03/20 15:06:38 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_exec_bin(t_args *tmp, char **path_to_bins, char **env);
int ft_exec_build_in(char **arg, t_env **head);

void	ft_work_with_t_arg_lists(t_struct *strct)
{
	char **env;
	t_args *tmp;

	env = ft_create_env(strct->env_head);
	
	tmp = strct->args_head;
	while (tmp)
	{
		if (!(ft_exec_build_in(strct->args_head->arg, &strct->env_head)))
			ft_exec_bin(tmp, strct->path_to_bins, env);
		tmp = tmp->next;
	}
	ft_free_splited_array(env, ft_get_env_size(strct->env_head));
}

int	ft_exec_bin(t_args *tmp, char **path_to_bins, char **env)
{
	pid_t	pid;
	int		status;
	char	*abs_path_to_command;
	char	*tmp_str;
	int		i;
	
	abs_path_to_command = ft_strdup("");
	i = 0;
	
	if ((pid = fork()) == 0)
	{
		if (tmp->arg[i][0] == '/' || tmp->arg[i][0] == '.' || tmp->arg[i][0] == '~')
		{
			// printf("/ || . || ~\n");
			if ((execve(tmp->arg[0], tmp->arg, env)) == -1)
			{
				printf("my_bash: %s: No such file or directory\n", tmp->arg[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			while (path_to_bins[i])
			{
				tmp_str = abs_path_to_command;
				abs_path_to_command = ft_strjoin(path_to_bins[i++], tmp->arg[0]);
				free(tmp_str);
				execve(abs_path_to_command, tmp->arg, env);
				if (!path_to_bins[i])
				{
					printf("my_bash: %s: command not found\n", tmp->arg[0]);
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	else
		waitpid(pid, &status, 0);
	// printf("FINISH\n");
	return (0);
}

int ft_exec_build_in(char **arg, t_env **head)
{
	(void)arg;
	(void)head;

	// printf("\nHERE SHOULD BE THE RESULT OF EXECUTION OF 'BUILD IN' COMMAND\n");
	return (0);
}