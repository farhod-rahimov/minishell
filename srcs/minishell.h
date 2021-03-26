/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:32:46 by btammara          #+#    #+#             */
/*   Updated: 2021/03/26 15:27:26 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  // wait()
#include "./libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <sys/errno.h>

#define HISTFILE "/tmp/minishell_hist.txt"
#define OUTPUT "/tmp/minishell_output.txt"

typedef struct flags
{
	int	signal_c;
}				t_flags;

typedef struct env
{
	char		*key;
	char		*value;
	struct	env	*next;
} t_env;

typedef struct red
{
	char		*type;
	char		*file_name;
	struct	red	*next;
} t_redirect;

typedef struct args
{
	char			**arg;			//args[0] = command, argsp[1 + ...] arguments	
	int				pipe;
	struct	args	*next;
	struct	args	*prev;
	int				redir_flag;
	t_redirect		*redir_head;
	int				right_redir;
	int				left_redir;
	int				exec_done;
} t_args;

typedef struct s
{
	char	*parsed_str;
	char	**path_to_bins;
	t_env	*env_head;
	t_args	*args_head;
	int		n_i;
	int		initial_fd[2];
	int		output_fd;
	int		exit_value;
} t_struct;

void	ft_free_splited_array(char ***array, int n);
void	ft_copy_old_str(char *old_buf, char *new_buf);


int		ft_show_prompt(t_struct *strct, int i);
void	ft_begin_parsing(t_struct *strct);


int		ft_parse(t_struct *strct, t_args *tmp_head, int i);

int		ft_parse_str_till_dq_ends(t_args **current_t_arg, int i, t_struct *strct);
// int		ft_copy_str_to_structure_t_args(t_args **tmp, char *str, int n_i);
void	ft_copy_str_to_structure_t_args(t_struct *strct, t_args **tmp, char *str, int n_i);
void	ft_push_backft_push_back_char(char **str, char c);
int		ft_check_if_new_list_or_arg_is_needed(t_struct *strct, t_args **current_t_arg, int i);
int		ft_copy_old_arg_to_new(t_args **new_arg, char **old_arg, int n_i);
void	ft_free_arg(char **tmp_arg);
void	ft_free_redir(t_redirect *head);


int		ft_parse_str_till_sq_ends(t_args **current_t_arg, int i, t_struct *strct);
int		ft_parse_str_till_env_var_ends(t_args **current_t_arg, int i, t_struct *strct);
int		ft_work_with_dollar(t_args **current_t_arg, int i, t_struct *strct);
int		ft_parse_str_till_it_ends(t_args **current_t_arg, int i, t_struct *strct);

t_args	*ft_create_new_t_args(t_struct *strct, t_args *prev_t_args);


void	ft_print_devided_args(t_args *head);


void	ft_structure_env(t_struct *strct, char **env);
void	ft_fill_t_env_list(t_env *env_list, char **env, int i, int k);
t_env	*ft_create_new_t_env(t_env *prev);
void	ft_get_path_to_bins(t_struct *strct);
void	ft_print_path_to_bins(char **path_to_bins);
void	ft_free_two_dimensional_array(char **array);
int		ft_skip_spaces(char *str, int i);
// void	ft_print_env(t_env *head);

// int		ft_get_command_e(t_struct *strct, int i);
// int		ft_get_command_c(t_struct *strct, int i);
// int		ft_get_command_p(t_struct *strct, int i);
// int		ft_get_command_u(t_struct *strct, int i);
// int		ft_get_command_semicolon(t_struct *strct, int i);
// int		ft_get_command_s_comma(t_struct *strct, int i);
// int		ft_get_command_d_comma(t_struct *strct, int i);
// int		ft_get_command_s_r_right(t_struct *strct, int i);
// int		ft_get_command_s_r_left(t_struct *strct, int i);
// int		ft_get_command_d_r_right(t_struct *strct, int i);
// int		ft_get_command_pipe(t_struct *strct, int i);

// VAR=echo && ls /usr/local/bin | grep $VAR ; ls /usr/bin | grep $VAR ; ls /bin | grep $VAR ; ls /usr/sbin | grep $VAR ; ls /sbin | grep $VAR ; ls /usr/local/munki | grep $VAR
// first second third fourth fifth sixth seventh eights nines tens 11th 12th 13th
// "1'$PATH' 2$PATH$PATH$PATH 3ballalalala 4$PATH 5PATH"

//"balalalalalala $PATH popopopopopopopop"
//"balalalalalala $PATH popopopopopopopop" 'jcvnwkejncwkjenckjwencvjkwenkjwe' ; "balalalalalala $PATH popopopopopopopop""balalalalalala $PATH popopopopopopopop"

void	ft_push_back_char(char **str, char c);
void	ft_write_malloc_error(void);
char	*ft_strdup_new(const char *s1);
char	*ft_strjoin_new(char const *s1, char const *s2);
void	ft_dup2_error(t_struct *strct);
void	ft_errno_error(t_struct *strct, char *file_name);
void	ft_strcopy(char *dst, char *src);
void	ft_work_with_t_arg_lists(t_struct *strct, t_args **tmp);
char	**ft_create_env(t_env *env_head);
int		ft_get_env_size(t_env *tmp);
void	ft_change_shell_level(t_env *env_head);
void	ft_print_env(t_env *head);
void	ft_push_back_redir_list(t_args **current_t_arg, t_redirect *redir_head, char *type, char *file_name);

int		ft_exec_bin(t_struct *strct, t_args *tmp, char **path_to_bins, char **env);
int		ft_exec_build_in(char **arg, t_env **head, t_struct *strct);
void    ft_left_redirect(t_struct *strct, t_args *args, int counter);
void ft_right_redirect(t_struct *strct, t_args *args, char **env, int counter);

void    ft_pipe(t_struct *strct, int fd_pipe[2]);
void    ft_close_pipe_01_dup_initial_0(int fd_pipe[2], t_struct *strct);
void    ft_close_pipe_01_dup_initial_1(int fd_pipe[2], t_struct *strct);
int		ft_check_syntax(t_struct *strct, char *str);

//////////////////////////////////////////dickuordle

int		buildin(char **arg, t_env **env, int *exit_value);
void	ft_term(t_struct *strct);
int		ft_strcmp(const char *s1, const char *s2);
int		get_next_line(int fd, char **line);
char 	**ft_get_hist(t_struct *strct);
void	ft_interrupt(int signal);
void	ft_quit(int signal);
void	ft_read(char **hist, int *curpl, int hsize, char **str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_putchar(int c);
char	*ft_append(char *old, char *new);



t_flags g_flags;
// ls -la >0file ; ls -la | grep Makefile ; grep <0file >1file ;
