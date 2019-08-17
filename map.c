/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:58:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 20:41:54 by trobicho         ###   ########.fr       */
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
				map->buf[x + y * map->w] = 1;
			else
				map->buf[x + y * map->w] = 0;
			x++;
		}
		y++;
	}
	map->buf[4 + 60] = 1;
	return (0);
}

int		init_map(t_map *map)
{
	map->grid_len = 64;
	if (load_map_test(map))
		return (1);
	return (0);
}

int		check_grid(t_map *map, t_vec2i v)
{
	v.x /= map->grid_len;
	v.y /= map->grid_len;
	if (v.x < 0 || v.y < 0 || v.x >= map->w || v.y >= map->h)
		return (1);
	return (map->buf[v.x + v.y * map->w]);
}
