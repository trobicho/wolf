/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:58:07 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/08 14:42:27 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sret;

	if ((sret = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	i = 0;
	if (s)
	{
		while (i < len)
		{
			sret[i] = s[i + start];
			i++;
		}
	}
	sret[i] = '\0';
	return (sret);
	return (NULL);
}
