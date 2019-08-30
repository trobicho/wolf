/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:04:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/30 02:24:25 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppm.h"

ssize_t	read_unsigned_nb_until_space(int fd, ssize_t max)
{
	int		r;
	char	c;

	r = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (r > max)
			return (-1);
		if (ft_isdigit(c))
			r = r * 10 + c - '0';
		else if (ft_isspace(c))
			break ;
		else
			return (-1);
	}
	return (r);
}

int		ppm_parse_header(int fd, ssize_t *w, ssize_t *h)
{
	char	magic_buf[3];
	ssize_t	size;
	char	c;

	size = read(fd, magic_buf, 3);
	if (magic_buf[0] != 'P' || magic_buf[1] != '6' || !ft_isspace(magic_buf[2]))
		return (-1);
	if ((*w = read_unsigned_nb_until_space(fd, 10000)) == -1)
		return (-1);
	if ((*h = read_unsigned_nb_until_space(fd, 10000)) == -1)
		return (-1);
	if (*w < 1 || *h < 1)
		return (-1);
	if ((size = read_unsigned_nb_until_space(fd, 10000)) != 255)
		return (-1);
	return (0);
}
