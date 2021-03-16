/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btammara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 11:19:59 by btammara          #+#    #+#             */
/*   Updated: 2020/11/12 08:35:25 by btammara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ccounter(int n1)
{
	int counter;

	counter = 0;
	while (n1 != 0)
	{
		n1 = n1 / 10;
		counter++;
	}
	return (counter);
}

int			check_easy(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	else if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	return (0);
}

void		positive(int n, int fd)
{
	char	str[ccounter(n) + 1];
	int		count;
	int		i;

	count = ccounter(n);
	i = count;
	while (count-- > 0)
	{
		str[count] = n % 10 + 48;
		n = n / 10;
	}
	str[i] = '\0';
	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

void		negative(int n, int fd)
{
	char	str[ccounter(n) + 2];
	int		count;
	int		i;

	count = ccounter(n);
	n = n * -1;
	i = count;
	while (count >= 0)
	{
		str[count--] = n % 10 + 48;
		n = n / 10;
	}
	str[0] = '-';
	str[i + 1] = '\0';
	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	int	i;
	int count;

	count = ccounter(n);
	i = count;
	if ((check_easy(n, fd)))
		return ;
	if (n > 0)
		positive(n, fd);
	else
		negative(n, fd);
}
