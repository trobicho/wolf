/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:30:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/05 11:11:11 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_countpow(unsigned int n)
{
	unsigned int	r;

	r = 1;
	while (n >= 10)
	{
		n /= 10;
		r++;
	}
	return (r);
}

char		*ft_itoa(int n)
{
	int				isneg;
	char			*str;
	int				i;
	int				p;
	unsigned int	nbr;

	isneg = (n < 0 ? 1 : 0);
	nbr = (unsigned int)(isneg ? -n : n);
	p = ft_countpow(nbr);
	if ((str = (char*)malloc(sizeof(char) * (p + 1 + isneg))) == NULL)
		return (NULL);
	if (isneg)
		str[0] = '-';
	i = isneg;
	p = ft_powint(10, p - 1);
	while (p > 1)
	{
		str[i] = (nbr / p) % 10 + '0';
		p /= 10;
		i++;
	}
	str[i] = nbr % 10 + '0';
	str[i + 1] = '\0';
	return (str);
}
