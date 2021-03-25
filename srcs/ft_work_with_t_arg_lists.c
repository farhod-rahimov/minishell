/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_with_t_arg_lists.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:46:37 by btammara          #+#    #+#             */
/*   Updated: 2021/03/25 11:19:09 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static	void	ft_check_if_reset_01fds_needed(t_args *tmp, t_struct *strct, int fd_pipe[2]);
static	void	ft_check_pipe(t_args *tmp, t_struct *strct, char **env, int fd_pipe[2]);
static	void	ft_check_redirections(t_args *tmp, t_struct *strct, char **env);

void	ft_work_with_t_arg_lists(t_struct *strct, t_args **current_t_arg)
{
	t_redirect *tmp_red;
	tmp_red = strct->args_head->redir_head;

	int fd_pipe[2];
	char **env;

	env = ft_create_env(strct->env_head);

	ft_free_two_dimensional_array(strct->path_to_bins);	
	ft_get_path_to_bins(strct);
	
	while ((*current_t_arg)->prev != NULL)
		*current_t_arg = (*current_t_arg)->prev;
	
	while (*current_t_arg && (*current_t_arg)->exec_done == 0)
	{
		ft_check_redirections(*current_t_arg, strct, env);
		ft_check_pipe(*current_t_arg, strct, env, fd_pipe);
		if ((*current_t_arg)->left_redir)
			if (dup2(strct->initial_fd[0], 0) == -1)
				write(2, "dup2 ERROR\n", 11);
		(*current_t_arg)->exec_done = 1;
		if (((*current_t_arg) = (*current_t_arg)->next) == NULL)
		{
			ft_close_pipe_01_dup_initial_0(fd_pipe, strct);	
			break ;
		}
		ft_check_if_reset_01fds_needed(*current_t_arg, strct, fd_pipe);
	}
	ft_free_two_dimensional_array(env);	
}

void ft_free_two_dimensional_array(char **array)
{
	int i;

	i = 0;
	if (array)
	{
		while (array[i])
			free(array[i++]);
		free(array);
	}
}

int	ft_exec_bin(t_struct *strct, t_args *tmp, char **path_to_bins, char **env)
{
	(void)strct;
	pid_t	pid;
	int		status;
	char	*abs_path_to_command;
	char	*tmp_str;
	int		i;
	
	abs_path_to_command = NULL;
	i = 0;
	
	if ((pid = fork()) == 0)
	{
		abs_path_to_command = ft_strdup("");
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

static	void	ft_check_if_reset_01fds_needed(t_args *tmp, t_struct *strct, int fd_pipe[2])
{
	if (tmp)
	{
		if (tmp->prev)
		{
			if (tmp->prev->pipe)
			{
				close(fd_pipe[1]);
				if (dup2(fd_pipe[0], 0) == -1)
					write(2, "dup2 ERROR\n", 11);
				return ;
			}
		}
	}
	ft_close_pipe_01_dup_initial_0(fd_pipe, strct);	
}

static	void	ft_check_pipe(t_args *tmp, t_struct *strct, char **env, int fd_pipe[2])
{
	if (tmp->arg)
	{
		if (tmp->pipe)
		{
			ft_pipe(fd_pipe);
		}
		else if (tmp->prev)
		{
			if (tmp->prev->pipe)
				ft_close_pipe_01_dup_initial_1(fd_pipe, strct);	
		}
		if (!tmp->right_redir)
			if (!(ft_exec_build_in(tmp->arg, &strct->env_head)))
				ft_exec_bin(strct, tmp, strct->path_to_bins, env);
	}
}

static	void	ft_check_redirections(t_args *tmp, t_struct *strct, char **env)
{
	if (tmp->prev != NULL)
	{
		if (tmp->left_redir && !tmp->prev->pipe)
			ft_left_redirect(tmp, 0);
	}
	else if (tmp->prev == NULL && tmp->left_redir)
		ft_left_redirect(tmp, 0);

	if (tmp->right_redir)
		ft_right_redirect(strct, tmp, env, 0);
}

int ft_exec_build_in(char **arg, t_env **head)
{
	(void)arg;
	(void)head;


	// ft_change_shell_level(*head); /// это при запуске нашего минишелла
	// ft_print_env(*head);
	// printf("\nHERE SHOULD BE THE RESULT OF EXECUTION OF 'BUILD IN' COMMAND\n");
	return (buildin(arg, head));
}