/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 22:00:02 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/23 06:39:39 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physic.h"
#include "map.h"

static t_vec2i	calc_normal(t_vec2i pos, t_map *map, int push)
{
	t_vec2i	normal;
	int		dx;
	int		dy;
	t_vec2i	pos_temp;

	dx = pos.x - (int)(pos.x / map->grid_len) * map->grid_len;
	if (dx < map->grid_len / 2)
		dx = -(dx + push);
	else
		dx = (map->grid_len - dx) + push;
	dy = pos.y - (int)(pos.y / map->grid_len) * map->grid_len;
	if (dy < map->grid_len / 2)
		dy = -(dy + push);
	else
		dy = (map->grid_len - dy) + push;
	normal.x = 0;
	normal.y = 0;
	pos_temp = pos;
	pos_temp.x += dx;
	if((dx < 0 ? -dx : dx) < (dy < 0 ? -dy : dy) && check_grid(map, pos_temp) == 0)
		normal.x = dx;
	else
		normal.y = dy;
	return (normal);
}

void			physic_check(t_wolf *wolf)
{
	int		found;
	t_vec2i	normal;
	int		n;

	n = 0;
	while ((found = check_grid(&wolf->map, wolf->player.pos)) && n < 2)
	{
		normal = calc_normal(wolf->player.pos, &wolf->map, 5);
		printf("normal = (%d, %d)\n", normal.x, normal.y);
		wolf->player.pos.x += normal.x;
		wolf->player.pos.y += normal.y;
		n++;
	}
}
