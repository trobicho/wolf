/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:45:28 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/08 13:54:02 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == s2 || n == 0)
		return (1);
	if (s1 && s2)
	{
		while (s1[i] == s2[i] && s1[i] != '\0' && i < n)
		{
			i++;
		}
		if (s1[i] == s2[i] || i == n)
			return (1);
	}
	return (0);
}
