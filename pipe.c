/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:17:31 by btammara          #+#    #+#             */
/*   Updated: 2021/03/19 10:40:22 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)env;
	
	int intitial_fd_0 = dup(0);
	int intitial_fd_1 = dup(0);
	int fd_pipe[2];
	pid_t pid;
	int status;
	char *argv2[] = {"Makefile", "cmake-build-debug", "minishell", "pipe.c", "srcs"};
	
	printf ("PIPE %d\n", pipe(fd_pipe));
	if ((pid = fork()) == 0)
	{
		if ((dup2(fd_pipe[1], 1)) == -1)
			write(2, "1 dup2 error\n", 13);
		close(fd_pipe[0]);
		if ((execve("/bin/ls", argv2, env)) == -1)
			write(2, "1 error execve\n", 15);
	}
	else
	{
		if ((dup2(fd_pipe[0], 0)) == -1)
			write(2, "2 dup2 error\n", 14);
		close(fd_pipe[1]);
		waitpid(pid, &status, 0);
		close(fd_pipe[0]);
		
		if ((pid = fork()) == 0)
		{
			if ((execve("/usr/bin/grep", argv, env)) == -1)
				write(2, "2 error execve\n", 15);
		}
		else
		{
			waitpid(pid, &status, 0);
			if ((dup2(intitial_fd_0, 0)) == -1)
				write(2, "3 dup2 error\n", 13);
		}
	}
	write(1, "FINISH\n", 7);
	
	int ret;
	char c;
	while ((ret = read(0, &c, 1)) && ret != -1)
	{
		write(1, &c, 1);
	}

	return (0);
}