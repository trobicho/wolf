/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 22:00:02 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/07 02:18:10 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physic.h"
#include "map.h"

static t_vec2i	calc_normal(t_vec2i pos, int x)
{
	t_vec2i	normal;
	int		dx;
	int		dy;

	dx = pos.x - (int)(pos.x / 64) * 64;
	if (dx < 64 / 2)
		dx = -(dx);
	else
		dx = (64 - dx);
	dy = pos.y - (int)(pos.y / 64) * 64;
	if (dy < 64 / 2)
		dy = -(dy);
	else
		dy = (64 - dy);
	normal.x = 0;
	normal.y = 0;
	if (x)
		normal.x = dx;
	else
		normal.y = dy;
	return (normal);
}

static void		apply_physic_to_player(t_wolf *wolf, t_vec2i normal_tab[4])
{
	t_vec2i	normal;
	int		i;

	i = 0;
	normal = (t_vec2i){0, 0};
	while (i < 4)
	{
		if (i == 0 && normal_tab[i].x > 0)
			normal.x += normal_tab[i].x;
		else if (i == 2 && normal_tab[i].x < 0)
			normal.x += normal_tab[i].x;
		else if (i == 1 && normal_tab[i].y > 0)
			normal.y += normal_tab[i].y;
		else if (i == 3 && normal_tab[i].y < 0)
			normal.y += normal_tab[i].y;
		i++;
	}
	wolf->player.pos.x += normal.x;
	wolf->player.pos.y += normal.y;
}

static int		physic_check_door(t_wolf *wolf, t_vec2i pos, int found
	, int closing)
{
	t_door	*door;
	t_vec2i	pos_door;

	if (is_found_door(found))
	{
		pos_door = (t_vec2i){pos.x / 64, pos.y / 64};
		if ((door = find_that_door(wolf, pos_door)) != NULL)
		{
			if (door->state == door_state_open
				|| door->state == door_state_waiting_for_player_to_move_is_ass)
				return (0);
			else if (door->state == door_state_closing && closing)
			{
				door->state = door_state_waiting_for_player_to_move_is_ass;
				door->timer = 2;
				return (0);
			}
		}
	}
	return (1);
}

void			physic_check(t_wolf *wolf)
{
	int		found;
	t_vec2i	normal[4];
	t_vec2i	pos;
	int		i;

	if ((found = check_grid(&wolf->map, wolf->player.pos)))
		physic_check_door(wolf, wolf->player.pos, found, 1);
	i = 0;
	while (i < 4)
	{
		normal[i] = (t_vec2i){0, 0};
		pos = wolf->player.pos;
		if (i % 2 == 0)
			pos.x += (i == 0) ? -wolf->player.hb : wolf->player.hb;
		else
			pos.y += (i == 1) ? -wolf->player.hb : wolf->player.hb;
		if ((found = check_grid(&wolf->map, pos)))
		{
			if (physic_check_door(wolf, pos, found, 0))
				normal[i] = calc_normal(pos, (int)((i % 2) == 0));
		}
		i++;
	}
	apply_physic_to_player(wolf, normal);
}
