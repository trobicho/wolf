/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:30:35 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/09 16:04:40 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strmap(const char *s, char (*f)(char))
{
	size_t	i;
	char	*ret;

	i = 0;
	if (s && f)
	{
		while (s[i] != '\0')
		{
			i++;
		}
		if ((ret = malloc(sizeof(char) * i + 1)) == NULL)
			return (NULL);
		i = 0;
		while (s[i] != '\0')
		{
			ret[i] = f(s[i]);
			i++;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
