/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:29:29 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/05 18:44:32 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	ft_logten(int n)
{
	int	r;

	r = 1;
	while (n >= 10)
	{
		n /= 10;
		r *= 10;
	}
	return (r);
}

void		ft_putnbr_fd(int n, int fd)
{
	int	p;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *= -1;
		}
		p = ft_logten(n);
		while (p > 1)
		{
			ft_putchar_fd((n / p) % 10 + '0', fd);
			p /= 10;
		}
		ft_putchar_fd(n % 10 + '0', fd);
	}
}
