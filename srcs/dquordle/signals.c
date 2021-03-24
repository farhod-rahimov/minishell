#include "../minishell.h"

void	ft_interrupt(int signal)
{
//	pid_t pid;
//	int status;

	(void)signal;
	g_flags.signal_c = 1;
//	pid = waitpid(0, &status, WNOHANG);
//	if (pid == 0)
//		write(1, "\n", 1);  //daughter
//	else
		write(1, "\nmy_bash% ", 10);  //mommy
}

void	ft_quit(int signal)
{
	pid_t pid;
	int status;

	(void)signal;
	pid = waitpid(0, &status, WNOHANG);
	if (pid == 0)
		write(1, "Quit: 3\n", 8);  //daughter
}