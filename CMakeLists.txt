cmake_minimum_required(VERSION 3.17)
project(minishell_new C)

set(CMAKE_C_STANDARD 99)

include_directories(./srcs/libft)
add_subdirectory(./srcs/libft)

add_executable(minishell_new ./srcs/main.c
                            ./srcs/ft_structure_env.c
                            ./srcs/utils.c
                            ./srcs/ft_show_promt.c
                            ./srcs/parser/ft_parse.c
                            ./srcs/parser/new_utils.c
                            ./srcs/parser/ft_parse_str_till_env_var_ends.c
                            ./srcs/parser/ft_parse_str_till_it_ends.c
                            ./srcs/parser/ft_parse_str_till_sq_ends.c
                            ./srcs/parser/ft_parse_str_till_dq_ends.c
                            ./srcs/parser/ft_work_with_dollar.c
                            ./srcs/ft_work_with_t_arg_lists.c
                            ./srcs/ft_create_env.c
                            ./srcs/ft_change_shell_level.c
                            ./srcs/dquordle/builtins.c
                            ./srcs/dquordle/ft_get_hist.c
                            ./srcs/dquordle/gnl.c
                            ./srcs/dquordle/signals.c
                            ./srcs/dquordle/termcap.c)


target_link_libraries(minishell_new libft)