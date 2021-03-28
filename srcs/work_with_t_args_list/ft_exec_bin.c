/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:46:35 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 19:15:16 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_exec_binary(char **path_to_bins, t_args *tmp, char **env)
{
	int		i;
	char	*abs_path_to_command;
	char	*tmp_str;

	i = 0;
	abs_path_to_command = ft_strdup_new("");
	while (path_to_bins[i])
	{
		tmp_str = abs_path_to_command;
		abs_path_to_command = ft_strjoin_new(path_to_bins[i++], tmp->arg[0]);
		free(tmp_str);
		if (ft_strcmp(tmp->arg[0], ""))
			execve(abs_path_to_command, tmp->arg, env);
		if (!path_to_bins[i] && (tmp->right_redir != -1 && tmp->arg[0]))
		{
			free(abs_path_to_command);
			write(2, "my_bash: ", 9);
			write(2, tmp->arg[0], ft_strlen(tmp->arg[0]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
	}
}

static	void	part2_exec_bin(char **path_to_bins, t_args *tmp, \
			char *abs_path_to_command, char **env)
{
	if (path_to_bins)
		ft_exec_binary(path_to_bins, tmp, env);
	else
	{
		free(abs_path_to_command);
		write(2, "my_bash: ", 9);
		write(2, tmp->arg[0], ft_strlen(tmp->arg[0]));
		write(2, ": No such file or directory\n", 28);
		exit(127);
	}
}

static	void	part1_exec_bin(char **path_to_bins, t_args *tmp, \
			char *abs_path_to_command, char **env)
{
	if (ft_strlen(tmp->arg[0]) == 2 && !ft_strcmp(tmp->arg[0], ".."))
		return (ft_exec_binary(path_to_bins, tmp, env));
	if (ft_strlen(tmp->arg[0]) >= 3)
		if (!ft_strncmp(tmp->arg[0], "..", 2) && tmp->arg[0][2] != '/')
			return (ft_exec_binary(path_to_bins, tmp, env));
	if ((execve(tmp->arg[0], tmp->arg, env)) == -1)
	{
		write(2, "my_bash: ", 9);
		write(2, tmp->arg[0], ft_strlen(tmp->arg[0]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		if (errno == 2)
			exit(127);
		else if (errno == 13)
			exit(126);
		exit(EXIT_FAILURE);
	}
	free(abs_path_to_command);
}

void			ft_work_parent(t_struct *strct, pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (g_signal == 1)
		strct->exit_value = 130;
	else if (g_signal == 3)
		strct->exit_value = 131;
	else
		strct->exit_value = WEXITSTATUS(status);
}

void			ft_exec_bin(t_struct *strct, t_args *tmp, \
			char **path_to_bins, char **env)
{
	pid_t	pid;
	char	*abs_path_to_command;
	int		i;

	abs_path_to_command = NULL;
	i = 0;
	if ((pid = fork()) == 0)
	{
		if (tmp->redir_flag == -1)
			exit(1);
		abs_path_to_command = ft_strdup_new("");
		if (tmp->arg[i][0] == '/' || tmp->arg[i][0] == '.' \
			|| tmp->arg[i][0] == '~')
			part1_exec_bin(path_to_bins, tmp, abs_path_to_command, env);
		else
			part2_exec_bin(path_to_bins, tmp, abs_path_to_command, env);
	}
	else
		ft_work_parent(strct, pid);
}
