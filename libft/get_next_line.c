/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:03:35 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/21 01:32:21 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

static t_dlst	*ft_fdchr(const int fd)
{
	static t_dlst	lst = {NULL, 0, -1, NULL, NULL};
	t_dlst			*lret;
	int				nfd;

	lret = &lst;
	nfd = 0;
	if (fd <= 2 && fd != 0)
		return (NULL);
	while (lret->fd != -1 && lret->fd != fd)
	{
		if (lret->next && ++nfd)
			lret = lret->next;
		else
			break ;
	}
	if (lret->fd != -1 && lret->fd != fd)
	{
		if ((lret->next = (t_dlst*)malloc(sizeof(t_dlst))) == NULL)
			return (NULL);
		*(lret->next) = (t_dlst){NULL, 0, fd, lret, NULL};
		return (lret->next);
	}
	lret->fd = fd;
	return (lret);
}

static void		*ft_fdclose(t_dlst *lfd)
{
	free(lfd->buf);
	lfd->buf = NULL;
	if (lfd->prev)
	{
		if (lfd->next)
			lfd->next->prev = lfd->prev;
		lfd->prev->next = lfd->next;
		free(lfd);
	}
	else
		lfd->fd = -1;
	return (NULL);
}

static int		ft_joinf(t_dlst *lfd, char *buf, ssize_t size)
{
	char	*ptr;

	ptr = lfd->buf;
	lfd->buf = (char*)ft_memjoin(lfd->buf, buf, lfd->size, size);
	if (lfd->buf == NULL)
		return (-1);
	free(ptr);
	lfd->size += size;
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	t_dlst			*lfd;
	ssize_t			size;
	char			buf[BUFF_SIZE];
	char			*ptr;

	if ((lfd = ft_fdchr(fd)) == NULL)
		return (-1);
	while (line && (ptr = ft_strnchr(lfd->buf, lfd->size, '\n')) == NULL)
	{
		if ((size = read(fd, buf, BUFF_SIZE)) > 0)
			if (ft_joinf(lfd, buf, size) == -1)
				return (-1);
		if (size == 0 && lfd->size > 0)
		{
			*line = ft_strndup(lfd->buf, lfd->size + 1);
			return (*line == NULL ? -1 : (lfd->size = 0) + 1);
		}
		if (size < 1)
			return ((int)(*line = (char*)ft_fdclose(lfd)) + size);
	}
	if (!line || (*line = ft_strndup(lfd->buf, ++ptr - lfd->buf)) == NULL)
		return (-1);
	ft_memmove(lfd->buf, ptr, (lfd->size -= ptr - lfd->buf));
	return (1);
}
