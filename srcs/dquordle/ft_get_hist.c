/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:38:27 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/28 17:38:28 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_make_hist(t_list **head)
{
	char	**hist;
	int		i;
	t_list	*tmp;

	i = ft_lstsize(*head);
	if (!(hist = ft_calloc(i + 2, sizeof(char *))))
		ft_write_malloc_error();
	hist[i + 1] = NULL;
	while (*head)
	{
		hist[i--] = (*head)->content;
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	hist[0] = ft_strdup_new("");
	return (hist);
}

char	**ft_get_hist(t_struct *strct)
{
	int		fd;
	t_list	*head;
	t_list	*tmp;
	char	*line;

	line = NULL;
	head = NULL;
	if ((fd = open(HISTFILE, O_CREAT, 00777)) == -1)
		ft_file_error(HISTFILE);
	close(fd);
	if ((fd = open(HISTFILE, O_RDONLY)) == -1)
		ft_errno_error(strct, HISTFILE);
	while (get_next_line(fd, &line))
	{
		tmp = ft_lstnew(line);
		ft_lstadd_back(&head, tmp);
	}
	if (line)
	{
		tmp = ft_lstnew(line);
		ft_lstadd_back(&head, tmp);
	}
	close(fd);
	return (ft_make_hist(&head));
}
