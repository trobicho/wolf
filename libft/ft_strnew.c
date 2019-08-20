/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:08:21 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/08 14:05:44 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*buf;
	size_t	i;

	if (size + 1 < size)
		return (NULL);
	if ((buf = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		buf[i] = '\0';
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
