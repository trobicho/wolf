/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:06:56 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/09 16:09:27 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)(&s[i]));
	i -= 1;
	while (i >= 1)
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i--;
	}
	if (s[i] == (char)c)
		return ((char *)(&s[i]));
	return (NULL);
}
