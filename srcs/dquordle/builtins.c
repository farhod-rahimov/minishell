#include "../minishell.h"

void	ft_pwd(int *exit_value)
{
	char *buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	printf("%s\n", buf);
	free(buf);
	*exit_value = 0;
}

void	ft_echo(char **arg, int *exit_value)
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
	*exit_value = 0;
}


void	ft_env(char **arg, t_env *head, int *exit_value)
{
	t_env *tmp;
	char	*str;

	tmp = head;
	if (arg[1])
	{
		*exit_value = 2;
		return ;
	}
	while (tmp)
	{
		if (tmp->value)
		{
			str = ft_strdup(tmp->key);
			str = ft_append(str, "=");
			str = ft_append(str, tmp->value);
			str = ft_append(str, "\n");
			write(1, str, ft_strlen(str));
			free(str);
		}
		tmp = tmp->next;
	}
	*exit_value = 0;
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

int		valid(char *str)
{
	int i;
	int err;

	err = 0;
	if (ft_isdigit(str[0]))
		err++;
	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			err++;
		i++;
	}
	if (err)
	{
		write(2, "export: `", 9);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 26);
		return (0);
	}
	return (1);
}

int		ft_add_env(t_env **head, char *arg)
{
	char	*value;
	int		i;
	int		found;

	if (!valid(arg))
		return (1);
	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	value = NULL;
	if (arg[i])
		value = arg + i + 1;
	arg[i] = 0;
	found = 0;
	if (*head)
		found = ft_rewrite(*head, arg, value);
	if (!found)
		ft_new_env(head, arg, value);
	return (0);
}

//t_env	*ft_new_smth(char *key, char *value)
//{
//	t_env	*new;
//
//	new = (t_env *)malloc(sizeof(t_env));
//	new->value = ft_strdup(value);
//	new->key = ft_strdup(key);
//	new->next = NULL;
//	return (new);
//}

//  t_env	*ft_copy_list(t_env *head)
//  {
// 	t_env *tmp;
// 	t_env *new_head;
// 	t_env *new_tmp;

// 	tmp = head;
// 	new_tmp = new_head;
// 	while (tmp)
// 	{
// 		new_tmp->key = tmp->key;
// 		new_tmp->value = tmp->value;
// 		new_tmp->next = NULL;
// 		tmp = tmp->next;
// 	}
//  }

//t_env	*ft_sort_list(t_env *head)
//{
//	t_env	*new_head;
//	t_env	*tmp;
//	t_env	*prev;
//	int		flag;
//
//	flag = 1;
//	new_head = head; //ft_copy_list(head);
//	while (flag != 0)
//	{
//		flag = 0;
//		if (ft_strcmp(new_head->key, new_head->next->key) > 0)
//		{
//			tmp = new_head->next;
//			new_head->next = new_head->next->next;
//			tmp->next = new_head;
//			new_head = tmp;
//			flag++;
//		}
//		printf("lol\n");
//		prev = new_head;
//		tmp = new_head->next;
////		printf("%s\n%s\n", prev->key, tmp->key);
//		while (tmp->next)
//		{
////			printf("%s\n", tmp->key);
////			printf("%s\n", tmp->next->key);
//			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
//			{
//				prev->next = tmp->next;
//				tmp->next = tmp->next->next;
//				prev->next->next = tmp;
//				flag++;
//			}
//			else
//				tmp = tmp->next;
//			prev = prev->next;
//			//printf("kek\n");
//		}
//	}
//	return (new_head);
//}
//
//void	ft_export(char **arg, t_env **head)
//{
//	int i;
//	t_env *tmp;
//
//	if (*head && !arg[1])
//	{
//		*head = ft_sort_list(*head);
//		tmp = *head;
//		while (tmp)
//		{
//			printf("lol\n");
////			printf("declare -x %s", tmp->key);
//			write(1, "declare -x ", 11);
//		 	write (1, tmp->key, ft_strlen(tmp->key));
//			if (tmp->value)
//			{
//				write(1, "=", 1);
//				write(1, tmp->value, ft_strlen(tmp->value));
////				printf("=%s", tmp->value);
//			}
//			write(1, "\n", 1);
////			printf("\n");
//			tmp = tmp->next;
//		}
//	}
//	else
//	{
//		i = 1;
//		while (arg[i])
//			ft_add_env(head, arg[i++]);
//	}
//}

//char	*ft_join(t_env *tmp)
//{
//	char	*str;
//
//	str = ft_strdup("declare -x ");
//	str = ft_append(str, tmp->key);
//	if (tmp->value)
//	{
//		str = ft_append(str, "=\"");
//		str = ft_append(str, tmp->value);
//		str = ft_append(str, "\"");
//	}
//	return (str);
//}

void	ft_sort_arr(char **array)
{
	int i;
	int flag;
	char *tmp;

	flag = 1;
	while (flag != 0)
	{
		flag = 0;
		i = 0;
		while (array[i + 1])
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				flag++;
			}
			i++;
		}
	}
}

char	**ft_sp_to_arr(t_env *env_head)
{
	int     i;
	char    **env;
	t_env   *tmp;

	tmp = env_head;
	i = ft_get_env_size(tmp);
	if ((env = (char **)malloc(sizeof(char *) * i)) == NULL)
		exit(1);
	i = -1;
	while (tmp)
	{
		if (!(env[++i] = ft_strdup("declare -x ")))
			exit(1);
		env[i] = ft_append(env[i], tmp->key);
		if (tmp->value)
		{
			env[i] = ft_append(env[i], "=\"");
			env[i] = ft_append(env[i], tmp->value);
			env[i] = ft_append(env[i], "\"\n");
		}
		tmp = tmp->next;
	}
	env[++i] = NULL;
	ft_sort_arr(env);
	return (env);
}

void	ft_export(char **arg, t_env **head, int *exit_value)
{
	int i;
	char **env;

	if (*head && !arg[1])
	{
		env = ft_sp_to_arr(*head);
		i = -1;
		while (env[++i])
			write(1, env[i], ft_strlen(env[i]));
		i = 0;
		while (env[i])
			free(env[i++]);
		free(env);
		*exit_value = 0;
	}
	else
	{
		i = 1;
		while (arg[i])
			*exit_value += ft_add_env(head, arg[i++]);
	}
	if (*exit_value)
		*exit_value = 1;
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

void	ft_unset(char **arg, t_env **head, int *exit_value)
{
	t_env	*tmp;
	int i;

	i = 0;
	while (arg[++i])
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
	}
	*exit_value = 0;
}

void	ft_cd(char **arg, t_env **head, int *exit_value)
{
	char *new_pwd;
	char *buf;

	if (chdir(arg[1]) == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
//		printf("%s\n", strerror(errno));
		*exit_value = 1;
	}
	else
	{
		new_pwd = NULL;
		new_pwd = getcwd(new_pwd, 0);
		buf = ft_strjoin("PWD=", new_pwd);
		ft_add_env(head, buf);
		free(buf);
		free(new_pwd);
		*exit_value = 0;
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

void	ft_err_nar(char *str)
{
	write(2, "exit: ", 6);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	exit(255);
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
	num2 = -1;
	if (str[i] == '-' || str[i] == '+')
		m += str[i++] - '+';
	while (str[i])
	{
		num *= 10;
		num += str[i++] - 48;
	}
	if (num > num2 / 2  + 1 || (num == num2 / 2 + 1 && m == 0))
		ft_err_nar(str);
	if (m != 0)
		num = num2 / 2 + 1 - num;
	return (num % 256);
}

void	ft_exit(char **arg, int *exit_value)
{
	int ex_num;

	if (!arg[1])
		exit(*exit_value);
	if (ft_isnum(arg[1]) == 0)
		ft_err_nar(arg[1]);
	ex_num = ft_atol(arg[1]);
	if (!arg[2])
		exit(ex_num);
	else
	{
		write(2, "exit: too many arguments\n", 25);
		*exit_value = 1;
	}
}

int		buildin(char **arg, t_env **head, int *exit_value)
{
	if (!ft_strcmp(arg[0], "echo"))
		ft_echo(arg, exit_value);
	else if (!ft_strcmp(arg[0], "pwd"))
		ft_pwd(exit_value);
	else if (!ft_strcmp(arg[0], "cd"))
		ft_cd(arg, head, exit_value);
	else if (!ft_strcmp(arg[0], "env"))
		ft_env(arg, *head, exit_value);
	else if (!ft_strcmp(arg[0], "export"))
		ft_export(arg, head, exit_value);
	else if (!ft_strcmp(arg[0], "unset"))
		ft_unset(arg, head, exit_value);
	else if (!ft_strcmp(arg[0], "exit"))
		ft_exit(arg, exit_value);
	else
		return (0);
	return (1);
}