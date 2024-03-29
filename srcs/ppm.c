/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:08:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/07 02:20:58 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppm.h"
#include "ppm_load.h"
#include "ppm_utils.h"
#include "libft.h"
#include "map.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

static int	ppm_load_begin(const char *file_path, ssize_t *w, ssize_t *h)
{
	int	fd;

	get_next_byte(-1, NULL);
	if ((fd = open(file_path, O_RDONLY)) < 0)
		return (-1);
	if (ppm_parse_header(fd, w, h))
		return (-1);
	return (fd);
}

int			ppm_load_4bpp(const char *file_path, t_ppm_tex_4bpp *tex)
{
	int		fd;
	int		x;
	int		y;
	Uint32	byte;

	if ((fd = ppm_load_begin(file_path, &tex->w, &tex->h)) < 0
		|| (tex->pixels = malloc(sizeof(*tex->pixels) * tex->w * tex->h))
		== NULL)
		return (-1);
	y = -1;
	while (++y < tex->h)
	{
		x = -1;
		while (++x < tex->w)
		{
			if (get_next_byte(fd, ((Uint8*)&byte) + 2) != 0
				|| get_next_byte(fd, ((Uint8*)&byte) + 1) != 0
				|| get_next_byte(fd, ((Uint8*)&byte)) != 0)
				return (ppm_4bbp_load_error(fd, tex));
			tex->pixels[x + y * tex->w] = byte;
			if (tex->pixels[x + y * tex->w] == tex->blend)
				tex->pixels[x + y * tex->w] = 0xFF000000;
		}
	}
	return (close(fd));
}

int			ppm_load_1bpp_map(const char *file_path, t_ppm_tex_1bpp *map)
{
	int		fd;
	int		x;
	int		y;
	Uint8	byte;

	if ((fd = ppm_load_begin(file_path, &map->w, &map->h)) < 0
		|| map_alloc(map, map->w, map->h, 1))
		return (-1);
	y = 0;
	while (++y < map->h - 1)
	{
		x = 0;
		while (++x < map->w - 1)
		{
			if (get_next_byte(fd, &byte))
				return (map_load_error(fd, map));
			if (map_id_add(map, x, y, byte))
				return (map_load_error(fd, map));
		}
	}
	if (map->player_pos.x < 0 || map->player_pos.y < 0)
		return (map_load_error(fd, map));
	return (close(fd));
}

int			ppm_write_1bpp(const char *file_path, t_ppm_tex_1bpp *tex)
{
	int				fd;

	ft_putstr(file_path);
	ft_putstr("\n");
	if ((fd = open(file_path, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR)) < 0)
		return (-1);
	write(fd, "P6\n", 3);
	ft_putnbr_fd(tex->w, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(tex->h, fd);
	write(fd, "\n", 1);
	write(fd, "255\n", 4);
	write(fd, (void*)tex->pixels, tex->w * tex->h);
	close(fd);
	return (0);
}
