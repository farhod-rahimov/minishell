# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btammara <btammara@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/06 16:30:33 by btammara          #+#    #+#              #
#    Updated: 2021/03/12 08:31:55 by btammara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =			./srcs/main.c

OBJS =			$(SRCS:.c=.o)

GCC = 			gcc

FLAGS =			-Wall -Wextra -Werror

NAME =			minishell

LIBFT_NAME =	libft.a

%.o:			%.c
				@ $(GCC) $(FLAGS) -c $<
				@ mv ./*.o ./srcs/

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