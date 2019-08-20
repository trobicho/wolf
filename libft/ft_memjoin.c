/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:10:00 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/10 16:48:38 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memjoin(void const *s1, void const *s2, size_t l1, size_t l2)
{
	size_t	i;
	void	*sret;

	sret = NULL;
	if (l1 + l2)
	{
		if ((sret = malloc(sizeof(char) * (l1 + l2 + 1))) == NULL)
			return (NULL);
		i = 0;
		while (i < l1)
		{
			((char*)sret)[i] = ((char*)s1)[i];
			i++;
		}
		i = 0;
		while (i < l2)
		{
			((char*)sret)[i + l1] = ((char*)s2)[i];
			i++;
		}
	}
	return (sret);
}
