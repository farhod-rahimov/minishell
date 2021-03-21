/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 09:10:15 by btammara          #+#    #+#             */
/*   Updated: 2021/03/21 14:41:01 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	(void)argc;
	
	int initial_fd[2];
	initial_fd[0] = dup(0);
	initial_fd[1] = dup(1);

	int fd;
	
	pid_t pid;
	int status;

	char *command = "ls";
	char *argv2[] = {"ls -la", "-la", NULL};


	if ((pid = fork()) == 0)
	{
		if (argv[1][0] == '>' && argv[1][1] == '>')
		{
			if ((fd = open("new_file", O_CREAT | O_WRONLY | O_APPEND, 0766)) == -1)
				write(2, "fd errorr\n", 10);
		}
		else if (argv[1][0] == '>')
		{
			if ((fd = open("new_file", O_CREAT | O_WRONLY | O_TRUNC, 0766)) == -1)
				write(2, "fd errorr\n", 10);
		}
		if (dup2(fd, 1) == -1)
			write(2, "dup2 error\n", 11);
		if ((execve("/bin/ls", argv2, NULL)) == -1)
			write(2, "error execve\n", 15);
	}
	else
	{
		// waitpid(pid, &status, 0);
		wait(&status);
		while (1)
			;
	}
	
	
	
}
