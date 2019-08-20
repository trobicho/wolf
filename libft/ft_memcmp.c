/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 15:43:12 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/05 13:10:48 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1cmp;
	unsigned char	*s2cmp;

	s1cmp = (unsigned char *)s1;
	s2cmp = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1cmp[i] != s2cmp[i])
			return ((int)(s1cmp[i] - s2cmp[i]));
		i++;
	}
	return (0);
}
