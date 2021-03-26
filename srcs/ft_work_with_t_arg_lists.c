/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_with_t_arg_lists.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:46:37 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 17:22:12 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static	void	ft_check_if_reset_01fds_needed(t_args *tmp, t_struct *strct, int fd_pipe[2]);
static	void	ft_check_pipe(t_args *tmp, t_struct *strct, char **env, int fd_pipe[2]);
static	void	ft_check_redirections(t_args *tmp, t_struct *strct, char **env);

void	ft_work_with_t_arg_lists(t_struct *strct, t_args **current_t_arg)
{
	t_redirect *tmp_red;
	t_args *current_t_arg_head;
	tmp_red = strct->args_head->redir_head;

	int fd_pipe[2];
	char **env;

	if (!*current_t_arg)
		return ;
	env = ft_create_env(strct->env_head);

	ft_free_two_dimensional_array(strct->path_to_bins);	
	ft_get_path_to_bins(strct);

	while ((*current_t_arg)->prev != NULL)
		*current_t_arg = (*current_t_arg)->prev;
	current_t_arg_head = *current_t_arg;	
	while (*current_t_arg && (*current_t_arg)->exec_done == 0)
	{
		ft_check_redirections(*current_t_arg, strct, env);
		ft_check_pipe(*current_t_arg, strct, env, fd_pipe);
		if ((*current_t_arg)->left_redir)
			if (dup2(strct->initial_fd[0], 0) == -1)
				ft_dup2_error(strct);
		(*current_t_arg)->exec_done = 1;
		if (((*current_t_arg) = (*current_t_arg)->next) == NULL)
		{
			ft_close_pipe_01_dup_initial_0(fd_pipe, strct);	
			break ;
		}
		ft_check_if_reset_01fds_needed(*current_t_arg, strct, fd_pipe);
	}
	ft_free_two_dimensional_array(env);	
	ft_free_t_args(current_t_arg_head);
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
	pid_t	pid;
	int		status;
	char	*abs_path_to_command;
	char	*tmp_str;
	int		i;
	
	abs_path_to_command = NULL;
	i = 0;
	
	if ((pid = fork()) == 0)
	{
		abs_path_to_command = ft_strdup_new("");
		if (tmp->arg[i][0] == '/' || tmp->arg[i][0] == '.' || tmp->arg[i][0] == '~')
		{
			if ((execve(tmp->arg[0], tmp->arg, env)) == -1)
			{
				write (2, "my_bash: ", 9);
				write (2, tmp->arg[0], ft_strlen(tmp->arg[0]));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				if (errno == 2)
					exit(127);
				else if (errno == 13)
					exit (126);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			while (path_to_bins[i])
			{
				tmp_str = abs_path_to_command;
				abs_path_to_command = ft_strjoin_new(path_to_bins[i++], tmp->arg[0]);
				free(tmp_str);
				if (ft_strcmp(tmp->arg[0], ""))
					execve(abs_path_to_command, tmp->arg, env);
				if (!path_to_bins[i])
				{
					write (2, "my_bash: ", 9);
					write (2, tmp->arg[0], ft_strlen(tmp->arg[0]));
					write(2, ": command not found\n", 20);
					exit(127);
				}
			}
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (g_flags.signal_c)
			strct->exit_value = 130;
		else
			strct->exit_value = WEXITSTATUS(status);
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
					ft_dup2_error(strct);
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
			ft_pipe(strct, fd_pipe);
		}
		else if (tmp->prev)
		{
			if (tmp->prev->pipe)
				ft_close_pipe_01_dup_initial_1(fd_pipe, strct);	
		}
		if (!tmp->right_redir)
			if (!(ft_exec_build_in(tmp->arg, &strct->env_head, strct)))
				if (ft_strcmp(tmp->arg[0], ""))
					ft_exec_bin(strct, tmp, strct->path_to_bins, env);
	}
}

static	void	ft_check_redirections(t_args *tmp, t_struct *strct, char **env)
{
	if (tmp->prev != NULL)
	{
		if (tmp->left_redir && !tmp->prev->pipe)
			ft_left_redirect(strct, tmp, 0);
	}
	else if (tmp->prev == NULL && tmp->left_redir)
		ft_left_redirect(strct, tmp, 0);

	if (tmp->right_redir)
		ft_right_redirect(strct, tmp, env, 0);
}

int ft_exec_build_in(char **arg, t_env **head, t_struct *strct)
{
	// ft_change_shell_level(*head); /// это при запуске нашего минишелла
	// ft_print_env(*head);
	// printf("\nHERE SHOULD BE THE RESULT OF EXECUTION OF 'BUILD IN' COMMAND\n");
	return (buildin(arg, head, &(strct->exit_value)));
}