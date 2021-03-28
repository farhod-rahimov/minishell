/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:32:46 by btammara          #+#    #+#             */
/*   Updated: 2021/03/28 20:03:01 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <string.h>
# include <sys/errno.h>

# define HISTFILE "/goinfre/minishell_hist.txt"

int		g_signal;

typedef struct	s_en
{
	char		*key;
	char		*value;
	struct s_en	*next;
}				t_env;

typedef struct	s_r
{
	char		*type;
	char		*file_name;
	struct s_r	*next;
}				t_redirect;

typedef struct	s_ar
{
	char		**arg;
	int			pipe;
	struct s_ar	*next;
	struct s_ar	*prev;
	int			redir_flag;
	t_redirect	*redir_head;
	int			right_redir;
	int			left_redir;
}				t_args;

typedef	struct	s_s
{
	char	*parsed_str;
	char	**path_to_bins;
	t_env	*env_head;
	t_args	*args_head;
	int		n_i;
	int		initial_fd[2];
	int		output_fd;
	int		exit_value;
}				t_struct;

void			ft_copy_old_str(char *old_buf, char *new_buf);
void			ft_begin_parsing(t_struct *strct);
void			ft_free_t_args(t_args **head);
int				ft_parse_str_till_dq_ends(t_args **cur_t_arg, int i, \
				t_struct *strct);
void			ft_copy_str_to_structure_t_args(t_struct *strct, t_args **tmp, \
				char *str, int n_i);
int				ft_check_if_new_list_or_arg_is_needed(t_struct *strct, \
				t_args **cur_t_arg, int i);
int				ft_copy_old_arg_to_new(t_args **new_arg, \
				char **old_arg, int n_i);
void			ft_free_redir(t_redirect *head);
int				ft_parse_str_till_sq_ends(t_args **cur_t_arg, \
				int i, t_struct *strct);
int				ft_parse_str_till_env_var_ends(t_args **cur_t_arg, \
				int i, t_struct *strct);
int				ft_work_with_dollar(t_args **cur_t_arg, int i, t_struct *strct);
int				ft_parse_str_till_it_ends(t_args **cur_t_arg, \
				int i, t_struct *strct);
t_args			*ft_create_new_t_args(t_struct *strct, t_args *prev_t_args);
void			ft_check_if_reset_01fds_needed(t_args *tmp, \
				t_struct *strct, int fd_pipe[2]);
void			ft_check_pipe(t_args *tmp, t_struct *strct, \
				char **env, int fd_pipe[2]);
int				ft_check_redirections(t_args *tmp, t_struct *strct, char **env);
void			ft_structure_env(t_struct *strct, char **env);
t_env			*ft_create_new_t_env(t_env *prev);
void			ft_get_path_to_bins(t_struct *strct);
void			ft_free_two_dimensional_array(char **array);
int				ft_skip_spaces(char *str, int i);
void			ft_tolower_str(char *str);
void			ft_push_back_char(char **str, char c);
void			ft_write_malloc_error(void);
char			*ft_strdup_new(const char *s1);
char			*ft_strjoin_new(char const *s1, char const *s2);
void			ft_dup2_error(t_struct *strct);
void			ft_errno_error(t_struct *strct, char *file_name);
void			ft_strcopy(char *dst, char *src);
void			ft_work_with_t_arg_lists(t_struct *strct, t_args **tmp);
char			**ft_create_env(t_env *env_head);
int				ft_get_env_size(t_env *tmp);
void			ft_change_shell_level(t_env *env_head);
void			ft_push_back_redir_list(t_args **cur_t_arg, \
				t_redirect *redir_head, char *type, char *file_name);
void			ft_exec_bin(t_struct *strct, t_args *tmp, \
				char **path_to_bins, char **env);
int				ft_exec_build_in(t_args *tmp, t_env **head, t_struct *strct);
int				ft_left_redirect(t_struct *strct, t_args *args, int counter);
int				ft_right_redirect(t_struct *strct, t_args *args, \
				char **env, int counter);
void			ft_pipe(t_struct *strct, int fd_pipe[2]);
void			ft_close_pipe_01_dup_initial_0(int fd_pipe[2], t_struct *strct);
void			ft_close_pipe_01_dup_initial_1(int fd_pipe[2], t_struct *strct);
int				ft_check_syntax(t_struct *strct, char *str, int s_q, int d_q);
int				ft_remove_back_slash(char **str, int i);
char			*ft_create_str_from_2_char(char c1, char c2);
void			ft_free_if_error(t_struct *strct);
int				ft_print_syntax_error(t_struct *strct, char c);
char			*ft_str_from_char(char c);
int				buildin(char **arg, t_env **env, int *exit_value);
void			ft_term(t_struct *strct);
int				ft_strcmp(const char *s1, const char *s2);
int				get_next_line(int fd, char **line);
char			**ft_get_hist(t_struct *strct);
void			ft_interrupt(int signal);
void			ft_quit(int signal);
void			ft_read(char **hist, int *curpl, int hsize, char **str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_putchar(int c);
char			*ft_append(char *old, char *new);
void			ft_file_error(char *file);
void			ft_export(char **arg, t_env **head, int *exit_value);
int				ft_add_env(t_env **head, char *arg);
void			ft_new_env(t_env **head, char *key, char *value);
int				ft_get_size_env(t_env *tmp);
int				valid(char *str);
void			ft_unset(char **arg, t_env **head, int *exit_value);
void			ft_exit(char **arg, int *exit_value);
void			ft_env(char **arg, t_env *head, int *exit_value);
void			ft_cd(char **arg, t_env **head, int *exit_value);
void			ft_term_error(void);
void			ft_free_hist(char ***hist);
void			ft_add_command(t_struct *strct, char **hist, char *command);
void			ft_terminal_setup(t_struct *strct);
void			ft_terminal_backup(void);
void			ft_backspace_tab(char **hist, int curpl, char *str);

#endif
