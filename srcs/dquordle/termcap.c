#include "../minishell.h"

char	*ft_append(char *old, char *new)
{
	char	*newest;
	int		i;
	int		j;

	newest = (char *)malloc(ft_strlen(old) + ft_strlen(new) + 1);
	j = 0;
	i = -1;
	while (old[++i])
		newest[i] = old[i];
	while (new[j])
		newest[i++] = new[j++];
	newest[i] = 0;
	free(old);
	return (newest);
}

void	ft_add_command(char **hist, char *command)
{
	int fd;
	int i;

	i = 0;
	while (hist[i])
		i++;
	fd = open(HISTFILE, O_WRONLY | O_APPEND);
	if (i > 1)
		write(fd, "\n", 1);
	write(fd, command, ft_strlen(command));
	close(fd);
}

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

void	ft_backspace(char **hist, int curpl)
{
	if (hist[curpl][0])
	{
		tputs("\e[D", 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		int j = 0;
		while (hist[curpl][j])
			j++;
		if (j)
			hist[curpl][j - 1] = 0;
	}
}

void	ft_terminal_setup(t_struct *strct)
{
	struct termios term;
	t_env *temp;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	temp = strct->env_head;
	while (temp && ft_strcmp(temp->key, "TERM"))
		temp = temp->next;
//	if (!temp)
//		ft_error;
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

void	ft_prompt(char **str, char ***history, int *curpl)
{
	int hsize;
	char **hist;

	if (!g_flags.signal_c)
		write(1, "my_bash% ", 9);
	tputs(save_cursor, 1, ft_putchar);
	hist = ft_get_hist();
	*history = hist;
	hsize = 0;
	while (hist[hsize])
		hsize++;
	(*curpl) = 0;
	g_flags.signal_c = 0;
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
		if (g_flags.signal_c || !ft_strcmp(*str, "\n") ||
			(!ft_strcmp(*str, "\4") && hist[*curpl][0] == 0))
			break ;
		if (!ft_strcmp(*str, "\e[A") || !ft_strcmp(*str, "\e[B"))
			ft_arrow(hist, *str, curpl, hsize);
		else if (!strcmp(*str, "\177"))
			ft_backspace(hist, *curpl);
		else if (ft_strcmp(*str, "\e[C") && ft_strcmp(*str, "\e[D") &&
				 ft_strcmp(*str, "\4"))
		{
			write(1, *str, i);
			hist[*curpl] = ft_append(hist[*curpl], *str);
		}
		(*str)[0] = 0;
	}
}

void	ft_free_hist(char ***hist)
{
	int	i;

	i = 0;
	while ((*hist)[i])
		free((*hist)[i++]);
	free(*hist);
}

void	ft_term(t_struct *strct)
{
	char *str;
	int curpl;
	char **hist;

	str = (char *)malloc(1000);
	ft_bzero(str, 1000);
	while ((ft_strcmp(str, "\4")) || hist[curpl][0] != 0)
	{
		ft_terminal_setup(strct);
		ft_prompt(&str, &hist, &curpl);
		if (g_flags.signal_c)
			continue ;
		if (!(ft_strcmp(str, "\4")) && hist[curpl][0] == 0)
			break ;
		if (!ft_strcmp(str, "\n"))
		{
			str[0] = 0;
			if (hist[curpl][0] != 0)
				ft_add_command(hist, hist[curpl]);
		}
		strct->parsed_str = ft_strdup(hist[curpl]);
		ft_terminal_backup();
//		printf("\n%s\n", strct->parsed_str);
		write(1, "\n", 1);
		if (hist[curpl][0] != 0)
		{
			if (ft_begin_parsing(strct) == -1)
				exit(-1);
			ft_work_with_t_arg_lists(strct);
		}
		ft_free_hist(&hist);
	}
	write(1, "exit\n", 5);
}

