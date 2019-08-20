/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:00:16 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/04 22:43:37 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t n)
{
	void	*buf;

	if ((buf = malloc(n)) == NULL)
		return (NULL);
	ft_memset(buf, 0, n);
	return (buf);
}
