/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:08:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/25 16:32:50 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppm.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

static ssize_t	read_unsigned_nb_until_endl(int fd, ssize_t max)
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
			break;
		else
			return (-1);
	}
	return (r);
}

static int	ppm_parse_header(int fd, ssize_t *w, ssize_t *h)
{
	char	magic_buf[3];
	ssize_t	size;
	char	c;

	size = read(fd, magic_buf, 3);
	if (magic_buf[0] != 'P' || magic_buf[1] != '6' || !ft_isspace(magic_buf[2]))
		return (-1);
	if ((*w = read_unsigned_nb_until_endl(fd, 10000)) == -1)
		return (-1);
	if ((*h = read_unsigned_nb_until_endl(fd, 10000)) == -1)
		return (-1);
	if ((size = read_unsigned_nb_until_endl(fd, 10000)) != 255)
		return (-1);
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
	close(fd);
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
	tex->w = 64;
	tex->h = 64;
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
