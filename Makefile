# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btammara <btammara@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/06 16:30:33 by btammara          #+#    #+#              #
#    Updated: 2021/03/28 20:01:10 by btammara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =			./srcs/main.c \
				./srcs/ft_structure_env.c \
				./srcs/utils/utils_arg_1.c \
				./srcs/utils/utils_arg_2.c \
				./srcs/utils/utils_common.c \
				./srcs/utils/utils_env.c \
				./srcs/utils/utils_error_1.c \
				./srcs/utils/utils_error_2.c \
				./srcs/utils/utils_redir.c \
				./srcs/utils/ft_strdup_new.c \
				./srcs/utils/ft_strjoin_new.c \
				./srcs/parser/ft_parse.c \
				./srcs/parser/ft_parse_str_till_env_var_ends.c \
				./srcs/parser/ft_parse_str_till_it_ends.c \
				./srcs/parser/ft_parse_str_till_sq_ends.c \
				./srcs/parser/ft_parse_str_till_dq_ends.c \
				./srcs/parser/ft_work_with_dollar.c \
				./srcs/parser/ft_check_syntax.c \
				./srcs/work_with_t_args_list/ft_work_with_t_arg_lists.c \
				./srcs/work_with_t_args_list/ft_exec_bin.c \
				./srcs/work_with_t_args_list/ft_check.c \
				./srcs/ft_create_env.c \
				./srcs/ft_change_shell_level.c \
				./srcs/ft_left_redirect.c \
				./srcs/ft_right_redirect.c \
				./srcs/ft_pipe.c \
				./srcs/dquordle/builtins.c \
				./srcs/dquordle/ft_get_hist.c \
				./srcs/dquordle/gnl.c \
				./srcs/dquordle/signals.c \
				./srcs/dquordle/termcap.c \
				./srcs/dquordle/more_utils.c \
				./srcs/dquordle/export.c \
				./srcs/dquordle/unset.c \
				./srcs/dquordle/exit.c \
				./srcs/dquordle/cd_env.c \
				./srcs/dquordle/built_utils.c \
				./srcs/dquordle/term_utils.c

OBJS =			$(SRCS:.c=.o)

GCC = 			gcc

FLAGS =			-Wall -Wextra -Werror

NAME =			minishell

LIBFT_NAME =	libft.a

%.o:			%.c
				@ $(GCC) -c $(FLAGS) $< -o $(<:.c=.o)

all: 			make_libft $(NAME)

make_libft:		
				@ cd ./srcs/libft && make bonus && cp libft.a ../.. && cd ../..

$(NAME):		$(OBJS)
				@ $(GCC) -o $(NAME) $(OBJS) $(LIBFT_NAME) -ltermcap
				@ echo 'minishell built, run ./minishell'

clean:
				@ rm -f $(OBJS)
				@ cd ./srcs/libft && make clean && cd ../..

fclean:			clean
				@ rm -f $(NAME)
				@ cd ./srcs/libft && make fclean && cd ../..
				@ rm -f $(LIBFT_NAME)
				@ rm -f /goinfre/minishell_hist.txt

re:				fclean all

.PHONY:			all clean fclean re