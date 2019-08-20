/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:20:40 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/09 16:10:03 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static int	ft_nb_str(char *str, char c)
{
	char	*s;
	int		nb;
	int		last_letter;

	nb = 1;
	last_letter = 0;
	if (str == NULL)
		return (0);
	s = str;
	while (*s != '\0')
	{
		if (*s == c)
		{
			if (last_letter)
				nb++;
			last_letter = 0;
		}
		else
			last_letter = 1;
		s++;
	}
	return (nb - (1 - last_letter));
}

static char	*ft_strsplitlen(char *str, char c, size_t *l)
{
	int		lastletter;
	char	*r;

	*l = 0;
	lastletter = 0;
	r = str;
	while (*str)
	{
		if (*str == c)
		{
			if (lastletter)
				return (r);
		}
		else
		{
			if (!lastletter)
				r = str;
			lastletter = 1;
			*l += 1;
		}
		str++;
	}
	return (r);
}

static void	*ft_refree(char **ssplit, size_t l)
{
	size_t	i;

	i = 0;
	while (i < l)
		free(ssplit[i++]);
	free(ssplit);
	return (NULL);
}

static char	*loopi(char *str_split, char *str_tracker, size_t l)
{
	size_t	a;

	a = 0;
	while (a < l)
		str_split[a++] = *(str_tracker++);
	str_split[l] = '\0';
	return (str_tracker);
}

char		**ft_strsplit(const char *str, char c)
{
	size_t	i;
	size_t	l;
	size_t	nbstr;
	char	*str_tracker;
	char	**str_split;

	nbstr = ft_nb_str((char*)str, c);
	if ((str_split = (char**)malloc(sizeof(char*) * (nbstr + 1))) == NULL)
		return (NULL);
	i = 0;
	str_tracker = (char*)str;
	while (i < nbstr)
	{
		str_tracker = ft_strsplitlen(str_tracker, c, &l);
		if ((str_split[i] = (char*)malloc(sizeof(char) * (l + 1))) == NULL)
			return (ft_refree(str_split, i));
		str_tracker = loopi(str_split[i], str_tracker, l);
		i++;
	}
	str_split[nbstr] = 0;
	return (str_split);
}
