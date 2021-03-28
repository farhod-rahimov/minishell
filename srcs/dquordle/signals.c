#include "../minishell.h"

void	ft_interrupt(int signal)
{
	pid_t pid;
	int status;

	(void)signal;
	pid = waitpid(0, &status, WNOHANG);
	if (pid == 0)
		g_signal = 2;
	else
	{
		write(1, "\nmy_bash% ", 10);  //mommy
		g_signal = 1;
	}
}

void	ft_quit(int signal)
{
	pid_t pid;
	int status;

	(void)signal;
	g_signal = 3;
	pid = waitpid(0, &status, WNOHANG);
	if (pid == 0)
		write(1, "Quit: 3\n", 8);  //daughter
}