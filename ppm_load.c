/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 05:53:57 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/29 20:25:45 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppm.h"
#include "libft.h"
#include <unistd.h>

int	ppm_4bbp_load_error(int fd, t_ppm_tex_4bpp *tex)
{
	free(tex->pixels);
	close(fd);
	ft_putstr("invalid tex file\n");
	return (-1);
}

int	map_load_error(int fd, t_ppm_tex_1bpp *map)
{
	free(map->pixels);
	close(fd);
	ft_putstr("invalid map file\n");
	return (-1);
}

int	get_next_byte(int fd, Uint8 *byte)
{
	static int				cur_index = 0;
	static ssize_t			size = 0;
	static unsigned char	buf[READ_SIZE];
	static int				last_fd = -1;
	static int				total_size = 0;

	if (last_fd != fd || fd < 0)
	{
		cur_index = 0;
		last_fd = fd;
		if (fd > 0)
			size = read(fd, buf, READ_SIZE);
		else
			return (total_size = 0);
		total_size = size;
	}
	if (cur_index == size)
	{
		cur_index = 0;
		size = read(fd, buf, READ_SIZE);
		if (size <= 0)
			return (-1);
		total_size += size;
	}
	if (byte != NULL)
		*byte = (Uint8)buf[cur_index++];
	return (0);
}
