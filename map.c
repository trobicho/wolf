/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:58:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 16:37:05 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>

int	map_alloc(t_map *map, int w, int h)
{
	map->w = w;
	map->h = h;
	if ((map->pixels = malloc(sizeof(*map->pixels) * map->w * map->h)) == NULL)
		return (1);
	map->player_pos = (t_vec2i){-1, -1};
	return (0);
}

int	init_map(t_map *map)
{
	if (ppm_load_1bpp_map("./maps/save_map.ppm", map, 110))
		return (1);
	return (0);
}

int	check_grid(t_map *map, t_vec2i v)
{
	v.x /= 64;
	v.y /= 64;
	return (map->pixels[v.x + v.y * map->w]);
}

int	save_map(t_map *map)
{
	if (map->player_pos.x == -1 || map->player_pos.y == -1)
		ft_putstr("no player position have been set\n");
	else if (ppm_write_1bpp("./maps/save_map.ppm", map))
		ft_putstr("cannot save the map\n");
	else
	{
		ft_putstr("the map have been save to ./maps/save_map.ppm\n");
		return (0);
	}
	return (-1);
}
