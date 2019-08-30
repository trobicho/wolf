/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 04:34:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/30 06:27:05 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "map.h"
#include "vector.h"

static t_door	*add_door_to_list(t_wolf *wolf, t_vec2i pos)
{
	t_door	door;
	t_list	*ptr;

	door.pos = pos;
	door.state = door_state_open;
	door.timer = 64;
	if (wolf->door_list == NULL)
	{
		wolf->door_list = ft_lstnew((void*)&door, sizeof(t_door));
		ptr = wolf->door_list;
	}
	else
	{
		ptr = wolf->door_list;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = ft_lstnew((void*)&door, sizeof(t_door));
	}
	if (ptr != NULL)
		return ((t_door*)ptr->content);
	return (NULL);
}

static void		open_door(t_wolf *wolf, t_vec2i pos)
{
	t_door	*door_ptr;
	t_list	lptr;

	pos.x /= 64;
	pos.y /= 64;
	if ((door_ptr = find_that_door(wolf, pos)) == NULL)
	{
		if (door_ptr = add_door_to_list(wolf, pos) == -1)
			return ;
		printf("opening a door at [%d, %d]\n", pos.x, pos.y);
	}
	else
		printf("a door is open at [%d, %d]\n", pos.x, pos.y);
}

int				handle_action_event(t_wolf *wolf)
{
	t_vec2i	pos;
	int		range;
	int		i;

	i = 0;
	range = 20;
	while(i < 4)
	{
		pos = wolf->player.pos;
		pos.x += (i % 2 == 1 ? 0 : range - range * (int)(i / 2) * 2);
		pos.y += (i % 2 == 0 ? 0 : range - range * (int)(i / 2) * 2);
		if (is_found_door(check_grid(&wolf->map, pos)))
			open_door(wolf, pos);
		i++;
	}
}
