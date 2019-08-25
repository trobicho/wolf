/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:08:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/25 13:59:28 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppm.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

static int	ppm_parse_header(int fd, ssize_t *w, ssize_t *h)
{
	char	magic_buf[3];
	ssize_t	size;
	char	c;

	size = read(fd, magic_buf, 3);
	if (magic_buf[0] != 'P' || magic_buf[1] != '6' || !ft_isspace(magic_buf[2]))
		return (-1);
	while ((size = read(fd, &c, 1)) > 0)
	{
		printf("%c", c);
		if (c == '\n')
			break;
	}
	while ((size = read(fd, &c, 1)) > 0)
	{
		printf("%c", c);
		if (c == '\n')
			break;
	}
	*w = 384;
	*h = 1216;
	return (0);
}

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
	return (0);
}

int			ppm_load_1bpp(const char *file_path, t_ppm_tex_1bpp *tex)
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
			tex->pixels[x + y * 64] = ((Uint8)buf[cur_index]);
			x++;
			cur_index++;
		}
		y++;
	}
	return (0);
}

int			ppm_write_1bpp(const char *file_path, t_ppm_tex_1bpp *tex)
{
	int				fd;
	int				x;
	int				y;
	int				color;

	if ((fd = open(file_path, O_WRONLY)) <= 0)
		return (-1);
	write(fd, "P6", 2);
	ft_putnbr_fd(tex->w, fd);
	write(fd, "\n", 1);
	ft_putnbr_fd(tex->h, fd);
	write(fd, "\n", 1);
	write(fd, &tex->pixels, tex->w * tex->h);
	return (0);
}
