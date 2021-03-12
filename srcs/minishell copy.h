/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <btammara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:32:46 by btammara          #+#    #+#             */
/*   Updated: 2021/03/12 14:02:50 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  // wait()

typedef struct s
{
	char **path_to_bin;
	char *parsed_str;
} t_struct;

int		ft_show_prompt(t_struct *args);
void	ft_copy_old_buf(char *old_buf, char *new_buf);
void	ft_get_path_to_bin(char *s, t_struct *args);
int		ft_parse(t_struct *args, int i);