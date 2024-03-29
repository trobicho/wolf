/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 04:34:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/07 02:14:59 by trobicho         ###   ########.fr       */
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
	door.state = door_state_opening;
	door.timer = 64;
	door.w = 0.4;
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

	pos.x /= 64;
	pos.y /= 64;
	if ((door_ptr = find_that_door(wolf, pos)) == NULL)
	{
		if ((door_ptr = add_door_to_list(wolf, pos)) == NULL)
			return ;
	}
	if (door_ptr->state == door_state_closing)
	{
		door_ptr->state = door_state_opening;
		door_ptr->timer = 64 - door_ptr->timer;
	}
}

int				handle_action_event(t_wolf *wolf)
{
	t_vec2i	pos;
	int		range;
	int		i;
	int		found;

	i = 0;
	range = 20;
	while (i < 4)
	{
		pos = wolf->player.pos;
		pos.x += (i % 2 == 1 ? 0 : range - range * (int)(i / 2) * 2);
		pos.y += (i % 2 == 0 ? 0 : range - range * (int)(i / 2) * 2);
		if (is_found_door((found = check_grid(&wolf->map, pos))))
			open_door(wolf, pos);
		else if (found > 0 && found % 2 == 0)
			open_secret_door(wolf, pos, (t_vec2i){pos.x - wolf->player.pos.x
					, pos.y - wolf->player.pos.y});
		i++;
	}
	return (0);
}

static t_list	*del_a_door(t_wolf *wolf, t_list *ptr, t_list *ptr_last)
{
	if (ptr_last == NULL)
	{
		wolf->door_list = ptr->next;
		ptr_last = ptr->next;
	}
	else
		ptr_last->next = ptr->next;
	free(ptr->content);
	free(ptr);
	return (ptr_last);
}

void			handle_door_state(t_wolf *wolf)
{
	t_list	*ptr;
	t_list	*ptr_last;
	t_door	*door;

	ptr = wolf->door_list;
	ptr_last = NULL;
	while (ptr != NULL && (door = (t_door*)ptr->content) != NULL)
	{
		if (door->timer <= 0)
		{
			door->timer = (door->state == door_state_opening) ? 200 : 64;
			if (door->state == door_state_opening)
				door->state = door_state_open;
			else if (door->state == door_state_open
				|| door->state == door_state_waiting_for_player_to_move_is_ass)
				door->state = door_state_closing;
			else
				ptr = del_a_door(wolf, ptr, ptr_last);
			continue ;
		}
		door->timer--;
		ptr_last = ptr;
		ptr = ptr->next;
	}
}
