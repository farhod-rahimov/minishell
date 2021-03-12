/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:39:57 by btammara          #+#    #+#             */
/*   Updated: 2021/03/12 14:15:52 by btammara         ###   ########.fr       */
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
	return (ft_show_prompt(&args));
}

void	ft_get_path_to_bin(char *s, t_struct *args)
{
	args->path_to_bin = ft_split(s, ':');
	args->path_to_bin[0] = ft_strtrim(args->path_to_bin[0], "PATH=");

	// int i;
	// char **tmp;
	// i = 0;
	// tmp = args->path_to_bin;
	// while (tmp[i])
	// 	printf("%s\n", tmp[i++]);
}

int	ft_show_prompt(t_struct *args)
{
	char	*old_buf;
	char	c;
	int		i;
	int		ret;

	i = 1;
	if ((args->parsed_str = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (-1); //errno 12

	write(1, "my_bash ", 8);
	while ((ret = read(0, &c, 1)) == 1)
	{
		if (c == '\n')
			break;
		args->parsed_str[i - 1] = c;
		args->parsed_str[i++] = '\0';
		old_buf = args->parsed_str;
		if ((args->parsed_str = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
			return (-1); //errno 12
		ft_copy_old_buf(old_buf, args->parsed_str);
		free(old_buf);
	}
	printf("parsed str \"%s\"", args->parsed_str);
	return (ft_parse(args, 0));	
}

int		ft_parse(t_struct *args, int i)
{
	while (args->parsed_str[i] && args->parsed_str[i] != ';')
	{
		while (args->parsed_str[i] == ' ')
			i++;
		if (args->parsed_str[i] == 'e')
			i = ft_get_command_e(args, i);
		else if (args->parsed_str[i] == 'c')
			i = ft_get_command_c(args, i);
		else if (args->parsed_str[i] == 'p')
			i = ft_get_command_p(args, i);
		else if (args->parsed_str[i] == 'u')
			i = ft_get_command_u(args, i);
		else if (args->parsed_str[i] == ';')
			i = ft_get_command_semicolon(args, i);
		else if (args->parsed_str[i] == '\'')
			i = ft_get_command_s_comma(args, i);
		else if (args->parsed_str[i] == '\"')
			i = ft_get_command_d_comma(args, i);
		else if (args->parsed_str[i] == '>' && args->parsed_str[i + 1] != '>')
			i = ft_get_command_s_r_right(args, i);
		else if (args->parsed_str[i] == '<')
			i = ft_get_command_s_r_left(args, i);
		else if (args->parsed_str[i] == '>' && args->parsed_str[i + 1] == '>')
			i = ft_get_command_d_r_right(args, i);
		else if (args->parsed_str[i] == '|')
			i = ft_get_command_pipe(args, i);
	}
	
	if (args->parsed_str[i] != '\0')
		ft_parse(args, ++i);
	
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
