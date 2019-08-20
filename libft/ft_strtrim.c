/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:33:13 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/09 16:07:45 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_frontspace(char const *s, char **r)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	*r = (char *)&s[i];
	return (i);
}

static int	ft_backspace(char const *s)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = ft_strlen(s) - 1;
	while (&s[i] > s && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
	{
		len++;
		i--;
	}
	return (len);
}

char		*ft_strtrim(char const *s)
{
	char	*sret;
	char	*begin;
	size_t	i;
	size_t	len;

	if (s)
	{
		len = ft_strlen(s) - ft_frontspace(s, &begin) - ft_backspace(begin);
		if ((sret = malloc(sizeof(char) * (len + 1))) == NULL)
			return (NULL);
		i = 0;
		while (i < len)
		{
			sret[i] = begin[i];
			i++;
		}
		sret[i] = '\0';
		return (sret);
	}
	return (NULL);
}
