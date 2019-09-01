/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 19:56:38 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/01 21:02:10 by trobicho         ###   ########.fr       */
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

int	map_copy_crop(t_map *map, t_map *cpy, t_vec2i pos, SDL_Rect rect)
{
	int	m_y;

	m_y = 0;
	while (m_y < rect.h)
	{
		ft_memcpy(&map->pixels[pos.x + (pos.y + m_y) * map->h]
			, &cpy->pixels[rect.x + (rect.y + m_y) * cpy->w]
			, sizeof(*map->pixels) * rect.w);
		m_y++;
	}
	return (0);
}

int	map_copy(t_map *map, t_map *cpy)
{
	SDL_Rect	rect;
	t_vec2i		pos;

	pos = (t_vec2i){0, 0};
	rect = (SDL_Rect){0, 0, 0, 0};
	rect.w = map->w < cpy->w ? map->w : cpy->w;
	rect.h = map->h < cpy->h ? map->h : cpy->h;
	if (map->w < cpy->w)
		rect.x = (cpy->w - map->w) / 2;
	else if (map->w > cpy->w)
		pos.x = (map->w - cpy->w) / 2;
	if (map->h < cpy->h)
		rect.y = (cpy->h - map->h) / 2;
	else if (map->h > cpy->h)
		pos.y = (map->h - cpy->h) / 2;
	if (rect.x == 0)
		rect = (SDL_Rect){rect.x + 1, rect.y, rect.w - 2, rect.h};
	if (rect.y == 0)
		rect = (SDL_Rect){rect.x, rect.y + 1, rect.w, rect.h - 2};
	map->player_pos = cpy->player_pos;
	map->player_pos.x += pos.x - rect.x;
	map->player_pos.y += pos.y - rect.y;
	map->player_dir = cpy->player_dir;
	if (map_copy_crop(map, cpy, pos, rect))
		return (1);
	map->pixels[map->player_pos.x + map->player_pos.y * map->h]
		= 111 + map->player_dir;
}
