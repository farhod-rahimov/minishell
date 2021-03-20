/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_with_t_arg_lists.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:46:37 by btammara          #+#    #+#             */
/*   Updated: 2021/03/20 10:05:36 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_exec_command(t_struct *strct, t_args *tmp, char **path_to_bins);

void	ft_work_with_t_arg_lists(t_struct *strct)
{
	t_args *tmp;

	tmp = strct->args_head;
	while (tmp)
	{
		ft_exec_command(strct, tmp, strct->path_to_bins);
		tmp = tmp->next;
	}
}

void	ft_exec_command(t_struct *strct, t_args *tmp, char **path_to_bins)
{
	(void)tmp;
	(void)strct;
	(void)path_to_bins;
	char **tmp_arg;
	int status;

	tmp_arg = tmp->arg + 1;
	pid_t	pid;
	// // int		status;

	char	*abs_path_to_command;
	// char	*tmp_str;
	abs_path_to_command = ft_strdup("");
	// int i = 0;

	char *argv2[] = {"Makefile", "cmake-build-debug", "minishell", "pipe.c", "srcs", NULL};

	if ((pid = fork()) == 0)
	{
		execve("/bin/ls", argv2, NULL);
		printf("error");
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("FINISH\n");
	}
	// abs_path_to_command = ft_strjoin(path_to_bins[i], tmp->arg[0]);
	// printf("%s\n", abs_path_to_command);
	// printf ("%d\n", execve(abs_path_to_command, tmp->arg + 1, strct->env));
	// if ((pid = fork()) == 0)
	// {
		// while (path_to_bins[i])
		// {
		// 	tmp_str = abs_path_to_command;
		// 	abs_path_to_command = ft_strjoin(path_to_bins[i], tmp->arg[0]);
		// 	free(tmp_str);
		// 	printf("%s\n", abs_path_to_command);
		// 	printf ("%d\n", execve(abs_path_to_command, tmp->arg + 1, strct->env));
		// 	// execve(tmp->arg[0], tmp->arg + 1, NULL);
		// 	i++;
		// }
	// }
	// {
	// 	waitpid(pid, &status, 0);
	// 	if (WIFEXITED(status))
	// 		pritnf("program ended WITHOUT error\n");
	// 	else
	// 		pritnf("program ended WITH error\n");
	// }
	
}