/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_with_t_arg_lists.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:46:37 by btammara          #+#    #+#             */
/*   Updated: 2021/03/20 19:17:18 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_exec_bin(t_struct *strct, t_args *tmp, char **path_to_bins, char **env);
int ft_exec_build_in(char **arg, t_env **head);

void	ft_work_with_t_arg_lists(t_struct *strct)
{
	int fd_pipe[2];
	char **env;
	t_args *tmp;

	env = ft_create_env(strct->env_head);
	
	tmp = strct->args_head;
	while (tmp)
	{
		if (tmp->arg)
		{
			if (tmp->pipe)
			{
				if (pipe(fd_pipe) == -1)
					write(2, "pipe ERROR\n", 11);
				if (dup2(fd_pipe[1], 1) == -1)
					write(2, "dup2 ERROR\n", 11);
			}
			else
			{
				close(fd_pipe[0]);
				close(fd_pipe[1]);
				if (dup2(strct->initial_fd[1], 1) == -1)
					write(2, "dup2 ERROR\n", 11);
			}
			if (!(ft_exec_build_in(strct->args_head->arg, &strct->env_head)))
				ft_exec_bin(strct, tmp, strct->path_to_bins, env);
		}
		tmp = tmp->next;
		if (tmp)
		{
			if (tmp->prev)
			{
				if (tmp->prev->pipe)
				{
					close(fd_pipe[1]);
					if (dup2(fd_pipe[0], 0) == -1)
						write(2, "dup2 ERROR\n", 11);
				}
				else
				{
					close(fd_pipe[0]);
					close(fd_pipe[1]);
					if (dup2(strct->initial_fd[0], 0) == -1)
						write(2, "dup2 ERROR\n", 11);
				}
			}
			else
			{
				close(fd_pipe[0]);
				close(fd_pipe[1]);
				if (dup2(strct->initial_fd[0], 0) == -1)
					write(2, "dup2 ERROR\n", 11);
			}
		}
		else
		{
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			if (dup2(strct->initial_fd[0], 0) == -1)
			write(2, "dup2 ERROR\n", 11);
		}
	}
	ft_free_splited_array(env, ft_get_env_size(strct->env_head));
}

int	ft_exec_bin(t_struct *strct, t_args *tmp, char **path_to_bins, char **env)
{
	(void)strct;
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
	{
		waitpid(pid, &status, 0);
		// if (tmp->next)
		// 	if (!tmp->pipe && tmp->prev->pipe)   // если у текущего pipe = 0 && у предущего pipe != 0
		// 		if ((dup2(strct->initial_fd[0], 0)) == -1)
		// 			write(2, "3 dup2 error\n", 13);

	}
	// printf("FINISH\n");
	return (0);
}

int ft_exec_build_in(char **arg, t_env **head)
{
	(void)arg;
	(void)head;

	// ft_change_shell_level(*head); /// это при запуске нашего минишелла
	// ft_print_env(*head);
	// printf("\nHERE SHOULD BE THE RESULT OF EXECUTION OF 'BUILD IN' COMMAND\n");
	return (0);
}