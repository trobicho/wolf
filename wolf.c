/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:18:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/30 05:57:00 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "input.h"
#include "render.h"
#include "physic.h"
#include "libft.h"
#include "menu.h"
#include "editor.h"

static int	game_loop(t_wolf *wolf)
{
	while (!wolf->quit && wolf->state == state_game)
	{
		game_event(wolf);
		player_move(&wolf->player);
		physic_check(wolf);
		render_one_frame(wolf);
	}
	return (0);
}

int			state_loop(t_wolf *wolf)
{
	while (!wolf->quit)
	{
		if (wolf->state == state_game)
			game_loop(wolf);
		else if (wolf->state == state_menu)
			menu_state(wolf);
		else if (wolf->state == state_editor)
		{
			if (editor_state(wolf))
				return (1);
		}
	}
	return (0);
}

int			is_found_door(int id)
{
	if (id >= 99 && id <= 102)
		return 99;
	return (0);
}

t_door*		find_that_door(t_wolf *wolf, t_vec2i pos)
{
	t_list	*ptr;
	t_vec2i	pos_door;

	ptr = wolf->door_list;
	while (ptr != NULL)
	{
		pos_door = ((t_door*)ptr->content)->pos;
		if (pos.x == pos_door.x && pos.y == pos_door.y)
			return ((t_door*)ptr->content);
		ptr = ptr->next;
	}
	return (NULL);
}
