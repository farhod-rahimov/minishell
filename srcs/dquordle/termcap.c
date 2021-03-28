/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:39:07 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:39:08 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_arrow(char **hist, char *str, int *curpl, int hsize)
{
	if (!ft_strcmp(str, "\e[A"))
	{
		if (hsize - *curpl > 1)
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);
			(*curpl)++;
			write(1, hist[*curpl], ft_strlen(hist[*curpl]));
		}
	}
	else if (!ft_strcmp(str, "\e[B"))
	{
		if (*curpl > 0)
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);
			(*curpl)--;
			write(1, hist[*curpl], ft_strlen(hist[*curpl]));
		}
	}
}

void	ft_prompt(t_struct *strct, char **str, char ***history, int *curpl)
{
	int		hsize;
	char	**hist;

	if (g_signal == 2)
		write(1, "\n", 1);
	if (g_signal != 1 && g_signal != 3)
		write(1, "my_bash% ", 9);
	tputs(save_cursor, 1, ft_putchar);
	hist = ft_get_hist(strct);
	*history = hist;
	hsize = 0;
	while (hist[hsize])
		hsize++;
	(*curpl) = 0;
	g_signal = 0;
	ft_read(hist, curpl, hsize, str);
}

void	ft_read(char **hist, int *curpl, int hsize, char **str)
{
	int i;

	while (ft_strcmp(*str, "\n"))
	{
		i = 1;
		if ((*str)[0] == 0)
		{
			i = read(0, *str, 999);
			(*str)[i] = 0;
		}
		if (g_signal || !ft_strcmp(*str, "\n") ||
			(!ft_strcmp(*str, "\4") && hist[*curpl][0] == 0))
			break ;
		if (!ft_strcmp(*str, "\e[A") || !ft_strcmp(*str, "\e[B"))
			ft_arrow(hist, *str, curpl, hsize);
		else if (!strcmp(*str, "\177") || !ft_strcmp(*str, "\t"))
			ft_backspace_tab(hist, *curpl, *str);
		else if (ft_strcmp(*str, "\e[C") && ft_strcmp(*str, "\e[D") &&
					ft_strcmp(*str, "\4"))
		{
			write(1, *str, i);
			hist[*curpl] = ft_append(hist[*curpl], *str);
		}
		(*str)[0] = 0;
	}
}

void	ft_send_func(char *str, t_struct *strct, char ***hist, int curpl)
{
	if (!ft_strcmp(str, "\n"))
	{
		str[0] = 0;
		if ((*hist)[curpl][0] != 0)
			ft_add_command(strct, *hist, (*hist)[curpl]);
	}
	strct->parsed_str = ft_strdup_new((*hist)[curpl]);
	ft_terminal_backup();
	write(1, "\n", 1);
	if ((*hist)[curpl][0] != 0)
		ft_begin_parsing(strct);
	ft_free_hist(hist);
}

void	ft_term(t_struct *strct)
{
	char	*str;
	int		curpl;
	char	**hist;

	if (!(str = (char *)ft_calloc(1000, 1)))
		ft_write_malloc_error();
	while ((ft_strcmp(str, "\4")) || hist[curpl][0] != 0)
	{
		ft_terminal_setup(strct);
		ft_prompt(strct, &str, &hist, &curpl);
		if (g_signal != 0 && g_signal != 3)
		{
			ft_free_hist(&hist);
			strct->exit_value = 1;
			continue;
		}
		if (!(ft_strcmp(str, "\4")) && hist[curpl][0] == 0)
			break ;
		ft_send_func(str, strct, &hist, curpl);
	}
	write(1, "exit\n", 5);
	exit(strct->exit_value);
}
