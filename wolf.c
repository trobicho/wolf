/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:18:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/23 08:06:47 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "input.h"
#include "render.h"
#include "physic.h"
#include "libft.h"
#include "menu.h"

static int		game_loop(t_wolf *wolf)
{
	while (!wolf->quit && wolf->state == state_game)
	{
		game_event(wolf);
		physic_check(wolf);
		render_one_frame(wolf);
	}
	return (0);
}

int				state_loop(t_wolf *wolf)
{
	while (!wolf->quit)
	{
		if (wolf->state == state_game)
			game_loop(wolf);
		if (wolf->state == state_menu)
			menu_state(wolf);
	}
	return (0);
}
