/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 19:56:38 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/31 20:02:42 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>
#include "libft.h"

int	map_alloc(t_map *map, int w, int h, int add_border)
{
	int p;

	map->w = w + (add_border == 0 ? 0 : 2);
	map->h = h + (add_border == 0 ? 0 : 2);
	if ((map->pixels = malloc(sizeof(*map->pixels) * map->w * map->h)) == NULL)
		return (1);
	if (add_border)
		ft_memset((void*)map->pixels, 1, map->w * map->h);
	map->player_pos = (t_vec2i){-1, -1};
	return (0);
}

int	map_copy(t_map *map, t_map *cpy)
{
	map->w = cpy->w;
	map->h = cpy->h;
	if ((map->pixels = malloc(sizeof(*map->pixels) * map->w * map->h)) == NULL)
		return (1);
	if ((map->pixels = ft_memcpy(map->pixels, cpy->pixels
					, sizeof(*map->pixels) * map->w * map->h)) == NULL)
		return (1);
	map->player_pos = (t_vec2i){-1, -1};
	return (0);
}
