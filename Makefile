# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btammara <btammara@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/06 16:30:33 by btammara          #+#    #+#              #
#    Updated: 2021/03/20 15:24:12 by btammara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =			./srcs/main.c \
				./srcs/ft_structure_env.c \
				./srcs/utils.c \
				./srcs/ft_show_promt.c \
				./srcs/parser/ft_parse.c \
				./srcs/parser/new_utils.c \
				./srcs/parser/ft_parse_str_till_env_var_ends.c \
				./srcs/parser/ft_parse_str_till_it_ends.c \
				./srcs/parser/ft_parse_str_till_sq_ends.c \
				./srcs/parser/ft_parse_str_till_dq_ends.c \
				./srcs/parser/ft_work_with_dollar.c \
				./srcs/ft_work_with_t_arg_lists.c \
				./srcs/ft_create_env.c \
				./srcs/ft_change_shell_level.c

OBJS =			$(SRCS:.c=.o)

GCC = 			gcc

FLAGS =			-Wall -Wextra -Werror

NAME =			minishell

LIBFT_NAME =	libft.a

%.o:			%.c
				@ $(GCC) -c $(FLAGS) $< -o $(<:.c=.o)

all: 			make_libft $(NAME)

make_libft:		
				@ cd ./srcs/libft && make && cp libft.a ../.. && cd ../..

$(NAME):		$(OBJS)
				@ $(GCC) -o $(NAME) $(OBJS) $(LIBFT_NAME)
				@ echo 'minishell built, run ./minishell'

clean:
				@ rm -f $(OBJS)
				@ cd ./srcs/libft && make clean && cd ../..

fclean:			clean
				@ rm -f $(NAME)
				@ cd ./srcs/libft && make fclean && cd ../..
				@ rm -f $(LIBFT_NAME)

re:				fclean all

.PHONY:			all clean fclean re