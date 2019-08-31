/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:58:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/31 20:01:45 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>
#include "libft.h"

int	init_map(t_map *map)
{
	if (ppm_load_1bpp_map("./maps/save_map.ppm", map))
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

int	map_id_add(t_map *map, int x, int y, Uint8 id)
{
	int max_id;

	max_id = 114;
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (-1);
	if (id > max_id)
		return (-1);
	else if (id > max_id - 4)
	{
		if (map->player_pos.x > 0 || map->player_pos.y > 0)
			return (-1);
		map->pixels[x + y * map->w] = 0;
		map->player_pos = (t_vec2i){x, y};
		map->player_dir = id - (max_id - 3);
	}
	else
		map->pixels[x + y * map->w] = id;
	return (0);
}
