#include <stdio.h>
#include "minishell.h"

//int main()
//{
//    printf("Hello, World!\n");
//    buildin("echo", "lol");
//	buildin("echo", "-n lol");
//	buildin("pwd", NULL);
//	buildin("cd", "./lol");
//	buildin("cd", "../../");
//	buildin("pwd", NULL);
//    return 0;
//}
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_struct strct;
	int fd;

	g_flags.signal_c = 0;
	fd = open(HISTFILE, O_CREAT, 00777);
	close(fd);
	signal(SIGINT, ft_interrupt);
	signal(SIGQUIT, ft_quit);
	ft_structure_env(&strct, env);
	ft_term(&strct);

//	t_env *envv;


//	char *arg[4];
//	arg[0] = ft_strdup("export");
//	arg[1] = ft_strdup("lolo=kek");
//	arg[2] = ft_strdup("kek");
//	arg[3] = NULL;
//	if (ft_structure_env(&strct, env) == -1)
//		return (-1);
//	envv = strct.env_head;
//	buildin(arg, &envv);
//	printf("\n\n");
//	arg[1] = NULL;
//	buildin(arg, &envv);
//	printf("\n\n");
//	arg[0] = "env";
//	buildin(arg, &envv);
//	printf("\n\n");
//	arg[0] = "unset";
//	arg[1] = ft_strdup("lol");
//	arg[2] = ft_strdup("kek");
//	buildin(arg, &envv);
//	arg[0] = "export";
//	arg[1] = NULL;
//	buildin(arg, &envv);
//	arg[0] = "exit";
//	arg[1] = "512l34";
//	arg[2] = "123";
//	arg[1] = NULL;
//	buildin(arg, &envv);

//	return (ft_show_prompt(&strct));
	//return (0);
}

//int	ft_show_prompt(t_struct *strct)
//{
//	char	*old_parsed_str;
//	char	c;
//	int		i;
//	int		ret;
//
//	i = 1;
//	if ((strct->parsed_str = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
//		return (-1); //errno 12
//
//	write(1, "my_bash% ", 9);
//	while ((ret = read(0, &c, 1)) == 1)
//	{
//		if (c == '\n')
//			break;
//		strct->parsed_str[i - 1] = c;
//		strct->parsed_str[i++] = '\0';
//		old_parsed_str = strct->parsed_str;
//		if ((strct->parsed_str = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
//			return (-1); //errno 12
//		ft_copy_old_str(old_parsed_str, strct->parsed_str);
//		free(old_parsed_str);
//	}
//	printf("parsed str \"%s\"\n", strct->parsed_str);
//
//	if ((strct->args_head = ft_create_new_t_args(NULL)) == NULL)
//		return (-1); // malloc error
//	strct->n = 0;
//	strct->n_i = 0;
//
//	if ((ft_parse(strct, strct->args_head, 0)) == -1)
//		return (-1);
//	ft_print_devided_args(strct->args_head);
//	return (0);
//}
//
//
//void	ft_copy_old_str(char *old_buf, char *new_buf)
//{
//	int	len;
//	int	i;
//
//	len = ft_strlen(old_buf);
//	i = 0;
//	while (i < len)
//	{
//		new_buf[i] = old_buf[i];
//		i++;
//	}
//	new_buf[i] = '\0';
//}