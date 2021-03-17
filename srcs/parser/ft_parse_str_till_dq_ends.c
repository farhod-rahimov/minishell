/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str_till_dq_ends.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:56:32 by btammara          #+#    #+#             */
/*   Updated: 2021/03/17 14:55:45 by btammara         ###   ########.fr       */
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

int		ft_parse_str_till_dq_ends(t_args **current_t_arg, int i, t_struct *strct, int k)
{
	char	*str;
	char	*tmp;
	(void)k;
	(void)current_t_arg;
	
	if (!(str = ft_strdup("")))
		ft_error();
	while (strct->parsed_str[i] && strct->parsed_str[i] != '\"')
	{
		tmp = str;
		str = ft_push_back_char(str, strct->parsed_str[i++]);
		free(tmp);
	}
	printf("str %s\n", str);
	exit(1);

	return (i);
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