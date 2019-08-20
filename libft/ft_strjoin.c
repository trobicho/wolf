/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:06:11 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/09 16:04:12 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_cps2(char *sret, char const *s2, size_t len)
{
	int i;

	i = 0;
	if (s2)
	{
		while (s2[i] != '\0')
		{
			sret[i + len] = s2[i];
			i++;
		}
		sret[i + len] = '\0';
	}
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len;
	char	*sret;

	sret = NULL;
	if (s1 || s2)
	{
		len = (s1 ? ft_strlen(s1) : 0) + (s2 ? ft_strlen(s2) : 0);
		if ((sret = malloc(sizeof(char) * (len + 1))) == NULL)
			return (NULL);
	}
	len = 0;
	if (s1)
	{
		i = 0;
		while (s1[i] != '\0')
		{
			sret[i] = s1[i];
			len++;
			i++;
		}
	}
	ft_cps2(sret, s2, len);
	return (sret);
}
