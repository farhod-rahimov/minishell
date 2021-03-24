#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minishell.h"
#include <sys/errno.h>

int			error_code;

void	ft_pwd(void)
{
	char *buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	printf("%s\n", buf);
	free(buf);
}

void	ft_echo(char **arg)
{
	int i;
	int n;

	n = 0;
	if (!arg[1])
		return;
	i = 1;
	if (!ft_strcmp(arg[1], "-n"))
		i+= ++n;
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
}

void	ft_cd(char **arg)
{
	printf("%s\n", arg[1]);
	if (chdir(arg[1]) == -1)
		printf("%s\n", strerror(errno));
}

void	ft_env(t_env *head)
{
	t_env *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->value)
		{
//			printf("%s", tmp->key);
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
//			printf("=%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
}

void	ft_new_env(t_env **head, char *key, char *value)
{
	t_env	*new_env;
	t_env	*tmp;

	if ((new_env = (t_env *)malloc(sizeof(t_env))) == NULL)
		exit (-1); // ft_error
	new_env->next = NULL;
	new_env->key = ft_strdup(key);
	new_env->value = NULL;
	if (value)
		new_env->value = ft_strdup(value);
	if (!(*head))
		*head = new_env;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}

int		ft_rewrite(t_env *head, char *key, char *value)
{
	t_env *tmp;

	tmp = head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (value)
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_add_env(t_env **head, char *arg)
{
	char *value;
	int i;
	int found;

	//// VALIDATE
	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	value = NULL;
	if (arg[i])
		value = arg + i + 1;
	arg[i] = 0;
	i = 0;
//	while (arg[i])
//	{
//		if (!ft_isalnum(arg[i]) && arg[i] != '_')
//			ft_error();
//	}
	found = 0;
	if (*head)
		found = ft_rewrite(*head, arg, value);
	if (!found)
		ft_new_env(head, arg, value);
}

void	ft_export(char **arg, t_env **head)
{
	int i;
	t_env *tmp;

	tmp = *head;
	if (*head && !arg[1])
	{
		while (tmp)
		{
//			printf("declare -x %s", tmp->key);
			write(1, "declare -x ", 11);
		 	write (1, tmp->key, ft_strlen(tmp->key));
			if (tmp->value)
			{
				write(1, "=", 1);
				write(1, tmp->value, ft_strlen(tmp->value));
//				printf("=%s", tmp->value);
			}
			write(1, "\n", 1);
//			printf("\n");
			tmp = tmp->next;
		}
	}
	else
	{
		i = 1;
		while (arg[i])
			ft_add_env(head, arg[i++]);
	}
}


void	ft_del_one(t_env *head)
{
	t_env	*tmp;

	tmp = head->next;
	head->next = tmp->next;
	free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

void	ft_unset(char **arg, t_env **head)
{
	t_env	*tmp;
	int i;

	i = 1;
	while (arg[i])
	{
		tmp = *head;
		if (!ft_strcmp(tmp->key, arg[i]))
		{
			*head = (*head)->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		else
		{
			while (tmp && tmp->next)
			{
				if (!ft_strcmp(tmp->next->key, arg[i]))
					ft_del_one(tmp);
				tmp = tmp->next;
			}
		}
		i++;
	}
}

int		ft_isnum(char *str)
{
	int i;
	int s;

	i = 0;
	s = 0;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		s += ++i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if ((i > 20 && s == 1) || (i > 19 && s == 0))
		return (0);
	return (1);
}

int	ft_atol(char *str)
{
	unsigned long long int num;
	unsigned long long int num2;
	int i;
	int m;

	i = 0;
	num = 0;
	m = 0;
	num2 = -1;  //9223372036854775808
//	num2 /= 2;
//	printf("%llu", num2);
	if (str[i] == '-' || str[i] == '+')
		m += str[i++] - '+';
	while (str[i])
	{
		num *= 10;
		num += str[i++] - 48;
	}
	if (num > num2 / 2  + 1 || (num == num2 / 2 + 1 && m == 0))
	{
//		write(2, "exit: ", 6);
//		write(2, str, ft_strlen(str));
//		write(2, ": numeric argument required", 27);
		printf("exit: %s: numeric argument required", str);
		exit(255);
	}
	if (m != 0)
		num = num2 / 2 + 1 - num;
	return (num % 256);
}

void	ft_exit(char **arg)
{
	int ex_num;

	if (!arg[1])
		exit(error_code);
	if (ft_isnum(arg[1]) == 0)
	{
		write(2, "exit: ", 6);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": numeric argument required", 27);
		exit(255);
	}
	ex_num = ft_atol(arg[1]);
	if (!arg[2])
		exit(ex_num);
	else
		write(2, "exit: too many arguments\n", 25);
}

int		buildin(char **arg, t_env **head)
{
	error_code = 42;
	if (!ft_strcmp(arg[0], "echo"))
		ft_echo(arg);
	else if (!ft_strcmp(arg[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(arg[0], "cd"))
		ft_cd(arg);
	else if (!ft_strcmp(arg[0], "env"))
		ft_env(*head);
	else if (!ft_strcmp(arg[0], "export"))
		ft_export(arg, head);
	else if (!ft_strcmp(arg[0], "unset"))
		ft_unset(arg, head);
	else if (!ft_strcmp(arg[0], "exit"))
		ft_exit(arg);
	else
		return (0);
	return (1);
}