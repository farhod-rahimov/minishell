/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:32:46 by btammara          #+#    #+#             */
/*   Updated: 2021/03/21 17:26:59 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  // wait()
#include "./libft/libft.h"

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
} t_args;

typedef struct s
{
	char	*parsed_str;
	char	**path_to_bins;
	t_env	*env_head;
	t_args	*args_head;
	int		n_i;

	int		initial_fd[2];
} t_struct;

void	ft_free_splited_array(char **array, int n);
void	ft_copy_old_str(char *old_buf, char *new_buf);


int		ft_show_prompt(t_struct *strct, int i);
int		ft_begin_parsing(t_struct *strct);


int		ft_parse(t_struct *strct, t_args *tmp_head, int i);

int		ft_parse_str_till_dq_ends(t_args **current_t_arg, int i, t_struct *strct, int k);
// int		ft_copy_str_to_structure_t_args(t_args **tmp, char *str, int n_i);
int		ft_copy_str_to_structure_t_args(t_struct *strct, t_args **tmp, char *str, int n_i);
void	ft_push_backft_push_back_char(char **str, char c);
int		ft_check_if_new_list_or_arg_is_needed(t_struct *strct, t_args **current_t_arg, int i);
int		ft_copy_old_arg_to_new(t_args **new_arg, char **old_arg, int n_i);
void	ft_free_arg(char **tmp_arg);
void	ft_free_redir(t_redirect *head);


int		ft_parse_str_till_sq_ends(t_args **current_t_arg, int i, t_struct *strct, int k);
int		ft_parse_str_till_env_var_ends(t_args **current_t_arg, int i, t_struct *strct, int k);
int		ft_work_with_dollar(t_args **current_t_arg, int i, t_struct *strct);
int		ft_parse_str_till_it_ends(t_args **current_t_arg, int i, t_struct *strct, int k);

t_args	*ft_create_new_t_args(t_struct *strct, t_args *prev_t_args);
// int		ft_check_if_new_list_is_needed(t_struct *strct, t_args **current_t_arg, int i);
char	*ft_add_back_str(char *str, int k, char c);


// int		ft_check_if_new_list_is_needed(t_struct *strct, t_args **current_t_arg, int i);
// int		ft_copy_str_to_structure_args(t_args *tmp, char *str, int n_i);
int		ft_copy_old_arg_n_i_of_tmp(t_args *tmp, char **tmp_arg, int n_i);
void	ft_print_devided_args(t_args *head);


int		ft_structure_env(t_struct *strct, char **env);
void	ft_fill_t_env_list(t_env *env_list, char **env, int i, int k);
t_env	*ft_create_new_t_env(t_env *prev);
void	ft_get_path_to_bins(t_struct *strct);
void	ft_print_path_to_bins(char **path_to_bins);
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
void	ft_error();
void	ft_strcopy(char *dst, char *src);
void	ft_work_with_t_arg_lists(t_struct *strct);
char	**ft_create_env(t_env *env_head);
int		ft_get_env_size(t_env *tmp);
void	ft_change_shell_level(t_env *env_head);
void	ft_print_env(t_env *head);
void	ft_push_back_redir_list(t_args **current_t_arg, t_redirect *redir_head, char *type, char *file_name);
