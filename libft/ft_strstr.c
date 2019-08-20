/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:02:38 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/06 14:22:19 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *s, const char *chr)
{
	size_t	i;
	size_t	i2;
	size_t	c;

	i = 0;
	i2 = 0;
	if (chr[0] == '\0')
		return ((char *)s);
	while (s[i] != '\0')
	{
		i2 = i;
		c = 0;
		while (s[i2] != '\0' && chr[c] != '\0')
		{
			if (s[i2] != chr[c])
				break ;
			c++;
			i2++;
		}
		if (chr[c] == '\0')
			return ((char *)(&s[i]));
		i++;
	}
	return (NULL);
}
