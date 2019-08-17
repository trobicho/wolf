/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:58:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 17:41:53 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>

int		load_map_test(t_map *map)
{
	int	x;
	int	y;

	map->w = 10;
	map->h = 10;
	if ((map->buf = malloc(sizeof(*map->buf) * map->w * map->h)) == NULL)
		return (1);
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (x == 0 || y == 0 || x == map->w - 1 || y == map->h -1)
				map->buf[x + y * map->w] = '#';
			else
				map->buf[x + y * map->w] = '.';
			x++;
		}
		y++;
	}
	return (0);
}

int		init_map(t_map *map)
{
	map->grid_len = 64;
	if (load_map_test(map))
		return (1);
	return (0);
}
