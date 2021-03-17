/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_dq_ends.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:56:32 by btammara          #+#    #+#             */
/*   Updated: 2021/03/17 17:00:52 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* экраниолвание в "" \" \$ \\ */
// echo \  $PATH

/* экранирование в двойгых кавычках "\\, \$, \"" */

// нужно ли обрабатывать такое echo "$(PWD)"
//echo * \* "*" '*'
//ls * "*"
//echo "$" "\$" echo "$""\$" где записать пробел

static	char	*ft_push_back_char(char *str, char c);
static void		ft_work_with_spec_sym(char *str, int i, t_struct *strct);
static	int		ft_remove_back_slash(char *str, int i);
static	int		ft_get_env_var(char *str, int i, t_struct *strct);
static char		*ft_get_env_var_value(char *env_var, t_struct *strct);
static	void	ft_replace_env_key_to_its_value(char **str, char *env_value, int start_env_var, int len_env_var);

int		ft_parse_str_till_dq_ends(t_args **current_t_arg, int i, t_struct *strct, int k)
{
	char	*str;
	char	*tmp;
	(void)k;
	(void)current_t_arg;
	
	if (!(str = ft_strdup("")))
		ft_error();
	while (strct->parsed_str[i])
	{
		if (i > 0)
			if (strct->parsed_str[i] == '\"' && strct->parsed_str[i - 1] != '\\')
				break ; // i stopped at "
		tmp = str;
		str = ft_push_back_char(str, strct->parsed_str[i++]);
		free(tmp);
	}
	
	ft_work_with_spec_sym(str, 0, strct);
	printf("dq_ends str %s\n", str);
	exit(1);

	return (i);
}

static void		ft_work_with_spec_sym(char *str, int i, t_struct *strct)
{
	(void)strct;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\\' || str[i + 1] == '$' || str[i + 1] == '\"'))
		{
			i = ft_remove_back_slash(str, i);
			continue ;
		}
		else if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			i = ft_get_env_var(str, ++i, strct);
			continue ;
		}
		i++;
	}
}

static	int		ft_get_env_var(char *str, int i, t_struct *strct)
{
	char	*env_var;
	char	*env_key;
	int		start_env_var;
	(void)strct;

	start_env_var = i - 1;
	if (!(env_var = ft_strdup("")))
		ft_error();
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		env_key = env_var;
		env_var = ft_push_back_char(env_var, str[i++]);
		free(env_key);
	}

	// printf("env_key %s\n", env_var);
	env_key = env_var;
	env_var = ft_get_env_var_value(env_var, strct);
	// printf("env_value %s\n", env_var);
	if (env_var[0] != '\0')
		ft_replace_env_key_to_its_value(&str, env_var, start_env_var, ft_strlen(env_key) + 1);
	printf("str get_env_var %s\n", str);
	free(env_key);
	free(env_var);	
	return (i);
}

static	void	ft_replace_env_key_to_its_value(char **str, char *env_value, int start_env_var, int len_env_var)
{
	char *tmp1;
	char *tmp2;
	
	tmp1 = *str;
	// printf("str1 %s, start_env_var %d, len_env_var %d\n", *str, start_env_var, len_env_var);
	*str = ft_substr(*str, 0, start_env_var);	
	
	tmp2 = *str;
	*str = ft_strjoin(*str, env_value);
	free(tmp2);
	
	tmp2 = *str;
	*str = ft_strjoin(*str, tmp1 + start_env_var + len_env_var);
	free(tmp2);
	free(tmp1);
}

static char		*ft_get_env_var_value(char *env_var, t_struct *strct)
{
	t_env	*tmp;

	tmp = strct->env_head;
	while (tmp)
	{
		if (!ft_strncmp(env_var, tmp->key, ft_strlen(env_var) + ft_strlen(tmp->key)))
		{
			if ((env_var = ft_strdup(tmp->value)) == NULL)
				ft_error();
			return (env_var);
		}
		tmp = tmp->next;
	}
	if ((env_var = ft_strdup("")) == NULL)
		ft_error();
	return (env_var);
}

static	int		ft_remove_back_slash(char *str, int i)
{
	char	*tmp;
	int		initial_i;

	tmp = str;
	initial_i = i;
	while (str[i])
	{
		str[i] = tmp[i + 1];
		i++;
	}
	return (++initial_i);
}

static	char	*ft_push_back_char(char *str, char c)
{
	int		len;
	char	*new_str;
	
	len = ft_strlen(str);
	if (str == NULL)
	{
		if ((new_str = (char *)malloc(sizeof(char) * 2)) == NULL)
			ft_error();
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	if ((new_str = (char *)malloc(sizeof(char) * (len + 2))) == NULL)
		ft_error();
	ft_strcopy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

void	ft_error()
{
	write(1, "malloc error\n", ft_strlen("malloc error\n"));
	exit(1);
}

void	ft_strcopy(char *dst, char *src)
{
	int i;
	int max;

	i = 0;
	max = ft_strlen(src);
	while (i < max)
	{
		dst[i] = src[i];
		i++;
	}
}