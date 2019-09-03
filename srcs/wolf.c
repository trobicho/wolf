/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:18:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/03 06:23:43 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "input.h"
#include "render.h"
#include "physic.h"
#include "libft.h"
#include "menu.h"
#include "editor.h"
#include "player.h"

static int		game_loop(t_wolf *wolf)
{
	while (!wolf->quit && wolf->state == state_game)
	{
		game_event(wolf);
		player_move(&wolf->player);
		handle_door_state(wolf);
		handle_secret_door_state(wolf);
		physic_check(wolf);
		render_one_frame(wolf);
	}
	wolf->player.state = 0;
	return (0);
}

int				state_loop(t_wolf *wolf)
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

int				is_found_door(int id)
{
	if (id >= 99 && id <= 102)
		return (99);
	return (0);
}

t_door			*find_that_door(t_wolf *wolf, t_vec2i pos)
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

t_secret_door	*find_that_secret_door(t_wolf *wolf, t_vec2i pos)
{
	t_list	*ptr;
	t_vec2i	pos_door;

	ptr = wolf->secret_door_list;
	while (ptr != NULL)
	{
		pos_door = ((t_secret_door*)ptr->content)->pos;
		if (pos.x == pos_door.x && pos.y == pos_door.y)
			return ((t_door*)ptr->content);
		ptr = ptr->next;
	}
	return (NULL);
}
