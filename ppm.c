/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:08:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 14:05:20 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppm.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int			ppm_load_4bpp(const char *file_path, t_ppm_tex_4bpp *tex)
{
	int				fd;
	int				x;
	int				y;
	int				cur_index;
	ssize_t			size;
	unsigned char	buf[READ_SIZE];

	if ((fd = open(file_path, O_RDONLY)) <= 0)
		return (-1);
	if (ppm_parse_header(fd, &tex->w, &tex->h))
		return (-1);
	cur_index = 0;
	if ((tex->pixels = malloc(sizeof(*tex->pixels) * tex->w * tex->h)) == NULL)
		return (-1);
	size = read(fd, buf, READ_SIZE);
	y = 0;
	while (y < tex->h)
	{
		x = 0;
		while (x < tex->w)
		{
			if (cur_index == size)
			{
				size = read(fd, buf, READ_SIZE);
				cur_index = 0;
			}
			tex->pixels[x + y * tex->w] =
				((Uint32)buf[cur_index]) << 16
				| ((Uint32)buf[cur_index + 1]) << 8
				| ((Uint32)buf[cur_index + 2]);
			if (tex->pixels[x + y * tex->w] == tex->blend)
				tex->pixels[x + y * tex->w] = 0xFF000000;
			x++;
			cur_index += 3;
		}
		y++;
	}
	close(fd);
	return (0);
}

static int	map_load_error(int fd, t_ppm_tex_1bpp *map)
{
	//free(map->pixels);
	close(fd);
	ft_putstr("invalid map file\n");
	return (-1);
}

int			ppm_load_1bpp_map(const char *file_path, t_ppm_tex_1bpp *tex
	, int max_id)
{
	int				fd;
	int				x;
	int				y;
	int				cur_index;
	ssize_t			size;
	unsigned char	buf[READ_SIZE];

	if ((fd = open(file_path, O_RDONLY)) <= 0)
		return (-1);
	if (ppm_parse_header(fd, &tex->w, &tex->h))
		return (-1);
	if (tex->w != 62 || tex->h != 62)
		return (-1);
	cur_index = 0;
	if ((tex->pixels = malloc(sizeof(*tex->pixels) * 64 * 64)) == NULL)
		return (-1);
	tex->w = 64;
	tex->h = 64;
	tex->player_pos = (t_vec2i){-1, -1};
	ft_memset(tex->pixels, 1, 64 * 64);
	size = read(fd, buf, READ_SIZE);
	y = 1;
	while (y < 63)
	{
		x = 1;
		while (x < 63)
		{
			if (cur_index == size)
			{
				size = read(fd, buf, READ_SIZE);
				cur_index = 0;
			}
			if (buf[cur_index] > max_id + 4)
				return (map_load_error(fd, tex));
			else if (buf[cur_index] > max_id)
			{
				if (tex->player_pos.x != -1 || tex->player_pos.y != -1)
					return (map_load_error(fd, tex));
				tex->pixels[x + y * 64] = 0;
				tex->player_pos = (t_vec2i){x, y};
				tex->player_dir = buf[cur_index] - (max_id + 1);
			}
			else
				tex->pixels[x + y * 64] = ((Uint8)buf[cur_index]);
			x++;
			cur_index++;
		}
		y++;
	}
	if (tex->player_pos.x < 0 || tex->player_pos.y < 0)
		(map_load_error(fd, tex));
	close(fd);
	return (0);
}

int			ppm_write_1bpp(const char *file_path, t_ppm_tex_1bpp *tex)
{
	int				fd;
	int				x;
	int				y;
	int				color;

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
