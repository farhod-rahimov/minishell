/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:38:55 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:38:57 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_terminal_setup(t_struct *strct)
{
	struct termios	term;
	t_env			*temp;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	temp = strct->env_head;
	while (temp && ft_strcmp(temp->key, "TERM"))
		temp = temp->next;
	if (!temp)
		ft_term_error();
	tgetent(0, temp->value);
}

void	ft_terminal_backup(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &term);
}

void	ft_add_command(t_struct *strct, char **hist, char *command)
{
	int fd;
	int i;

	(void)strct;
	i = 0;
	while (hist[i])
		i++;
	if ((fd = open(HISTFILE, O_WRONLY | O_APPEND)) == -1)
		ft_file_error(HISTFILE);
	if (i > 1)
		write(fd, "\n", 1);
	write(fd, command, ft_strlen(command));
	close(fd);
}

void	ft_free_hist(char ***hist)
{
	int	i;

	i = 0;
	while ((*hist)[i])
		free((*hist)[i++]);
	free(*hist);
}

void	ft_backspace_tab(char **hist, int curpl, char *str)
{
	int j;

	if (!ft_strcmp(str, "\t"))
	{
		hist[curpl] = ft_append(hist[curpl], "    ");
		write(1, "    ", 4);
	}
	else
	{
		if (hist[curpl][0])
		{
			tputs("\e[D", 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
			j = 0;
			while (hist[curpl][j])
				j++;
			if (j)
				hist[curpl][j - 1] = 0;
		}
	}
}
