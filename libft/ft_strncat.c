/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:36:43 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/08 14:07:09 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*s1;
	char	*s2;
	size_t	i;

	s1 = dest;
	s2 = (char *)src;
	while (*(s1++) != '\0')
	{
	}
	s1--;
	i = 0;
	while (i < n && s2[i] != '\0')
	{
		*(s1++) = s2[i];
		i++;
	}
	*s1 = '\0';
	return (dest);
}
