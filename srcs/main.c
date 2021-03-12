/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:39:57 by btammara          #+#    #+#             */
/*   Updated: 2021/03/12 11:05:39 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_struct args;
	ft_get_path_to_bin(env[6], &args);
	return (ft_show_prompt());
}

void	ft_get_path_to_bin(char *s, t_struct *args)
{
	args->path_to_bin = ft_split(s, ':');
	args->path_to_bin[0] = ft_strtrim(args->path_to_bin[0], "PATH=");

	int i;
	char **tmp;
	
	i = 0;
	tmp = args->path_to_bin;
	while (tmp[i])
		printf("%s\n", tmp[i++]);
}

int	ft_show_prompt(void)
{
	char	*buf;
	char	*old_buf;
	char	c;
	int		i;
	int		ret;

	i = 1;
	if ((buf = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (-1); //errno 12

	write(1, "my_bash ", 8);
	while ((ret = read(0, &c, 1)) == 1)
	{
		if (c == '\n')
			break;
		buf[i - 1] = c;
		buf[i++] = '\0';
		old_buf = buf;
		if ((buf = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
			return (-1); //errno 12
		ft_copy_old_buf(old_buf, buf);
		free(old_buf);
	}
	printf("parsed str \"%s\"", buf);
	return (0);	
}

void	ft_copy_old_buf(char *old_buf, char *new_buf)
{
	int	len;
	int	i;

	len = ft_strlen(old_buf);
	i = 0;
	while (i < len)
	{
		new_buf[i] = old_buf[i];
		i++;
	}
	new_buf[i] = '\0';
}
