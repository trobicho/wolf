/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:48:01 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/08 14:03:46 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	srclen;
	char	*s;

	len = 0;
	s = (char*)src;
	srclen = ft_strlen(src);
	while (size > 0 && *dst)
	{
		len++;
		dst++;
		size--;
	}
	if (size < 1)
		return (srclen + len);
	while (size > 1 && *s)
	{
		*dst++ = *s++;
		size--;
	}
	if (size == 1 || *s == 0)
		*dst = '\0';
	return (srclen + len);
}
