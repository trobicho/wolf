/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:41:56 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/23 17:18:15 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*pass_first(const char *str, int *neg)
{
	int i;

	*neg = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		*neg = (str[i] == '-' ? -1 : 1);
		i++;
	}
	return ((char*)&str[i]);
}

static char	*detect_base(const char *str, int *base)
{
	int i;

	*base = 10;
	i = 0;
	if (*str == '0')
	{
		i++;
		*base = 8;
		if (str[1] == 'x')
		{
			*base = 16;
			i++;
		}
	}
	return ((char*)&str[i]);
}

long		ft_strtol(const char *str, char **endptr, int base)
{
	unsigned long	r;
	int				i;
	int				neg;
	char			*ptr;
	unsigned int	c;

	r = 0;
	if ((ptr = pass_first(str, &neg)) && base == 0)
	{
		ptr = detect_base(ptr, &base);
		if (base == 0 && (ptr = (char*)str))
			return (0);
	}
	i = 0;
	while (ft_isalnum(ptr[i]))
	{
		c = (unsigned int)ft_tolower(ptr[i]);
		c -= (c > '9' ? ('a' - 10) : '0');
		if (c >= (unsigned int)base)
			break ;
		r = r * base + c;
		i++;
	}
	*endptr = &ptr[i];
	return ((long)(neg * (long)r));
}
