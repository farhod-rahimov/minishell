cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

include_directories(./srcs/libft)
add_subdirectory(./srcs/libft)

add_executable(minishell
        ./srcs/main.c
        ./srcs/ft_structure_env.c
        ./srcs/utils.c
        ./srcs/ft_show_promt.c
        ./srcs/parser/ft_parse.c
        ./srcs/parser/p_utils_1.c
        ./srcs/parser/ft_parse_str_till_env_var_ends.c
        ./srcs/parser/ft_parse_str_till_it_ends.c
        ./srcs/parser/ft_parse_str_till_sq_ends.c )

target_link_libraries(minishell libft)