/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:54:36 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/23 07:14:45 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "init.h"
#include "math.h"

int			main(int ac, char **av)
{
	t_wolf	wolf;

	if (wolf_init(&wolf))
		return (1);
	if (init_map(&wolf.map))
		return (1);
	wolf.player.pos.x = wolf.map.w * wolf.map.grid_len / 2;
	wolf.player.pos.y = wolf.map.h * wolf.map.grid_len / 2;
	wolf.player.angle = 0.0;
	if (state_loop(&wolf))
		return (1);
	return (wolf_quit(&wolf));
}
