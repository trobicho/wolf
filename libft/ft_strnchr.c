/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:36:35 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/10 17:53:20 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnchr(const char *s, size_t n, int c)
{
	size_t	i;

	if (s)
	{
		i = 0;
		while (i < n)
		{
			if (s[i] == (char)c)
				return ((char *)(&s[i]));
			i++;
		}
	}
	return (NULL);
}
