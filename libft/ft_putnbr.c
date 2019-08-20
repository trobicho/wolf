/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:16:08 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/05 18:44:07 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	ft_logten(unsigned int n)
{
	unsigned int	r;

	r = 1;
	while (n >= 10)
	{
		n /= 10;
		r *= 10;
	}
	return (r);
}

void		ft_putnbr(int n)
{
	int				p;
	unsigned int	mn;

	if (n < 0)
	{
		ft_putchar('-');
		mn = -n;
	}
	else
		mn = n;
	p = ft_logten(mn);
	while (p > 1)
	{
		ft_putchar((mn / p) % 10 + '0');
		p /= 10;
	}
	ft_putchar(mn % 10 + '0');
}
