#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern int errno;

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_pwd(void)
{
	char *buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	printf("%s\n", buf);
	free(buf);
}

void	ft_echo(char **argv)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	if (i > 2 && arg[0] == '-' && arg[1] == 'n' && arg[2] == ' ')
		printf("%s", arg + 3);
	else
		printf("%s\n", arg);
}

void	ft_cd(char **argv)
{
	int check;

	check = chdir(argv[1]);
	if (check == -1)
	{
		if (errno == 2)
			printf("No such file or directory\n");
	}

	//errooooooors
}

void	buildin(char **argv, struct env)
{
	if (!ft_strcmp(argv[0], "echo"))
		ft_echo(argv);
	if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd();
	if (!ft_strcmp(argv[0], "cd"))
		ft_cd(argv, env);
}