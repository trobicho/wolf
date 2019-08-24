/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:58:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/24 17:46:21 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>

int		map_alloc(t_map *map, int w, int h)
{
	map->w = w;
	map->h = h;
	if ((map->pixels = malloc(sizeof(*map->pixels) * map->w * map->h)) == NULL)
		return (1);
	return (0);
}

int		load_map_test(t_map *map)
{
	int	x;
	int	y;

	if (map_alloc(map, 10, 10))
		return (1);
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (x == 0 || y == 0 || x == map->w - 1 || y == map->h -1)
				map->pixels[x + y * map->w] = 1;
			else
				map->pixels[x + y * map->w] = 0;
			x++;
		}
		y++;
	}
	map->pixels[4 + 60] = 1;
	return (0);
}

int		init_map(t_map *map)
{
	if (load_map_test(map))
		return (1);
	return (0);
}

int		check_grid(t_map *map, t_vec2i v)
{
	v.x /= 64;
	v.y /= 64;
	return (map->pixels[v.x + v.y * map->w]);
}
