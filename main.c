/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:54:36 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/31 20:24:45 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "init.h"
#include <math.h>
#include "libft.h"

int	main(int ac, char **av)
{
	t_wolf	wolf;

	ft_memset(&wolf, 0x0, sizeof(wolf));
	if (wolf_init(&wolf))
		return (1);
	if (init_map(&wolf.map))
		return (1);
	wolf.player.pos.x = wolf.map.w * 64 / 2;
	wolf.player.pos.y = wolf.map.h * 64 / 2;
	wolf.player.angle = 0.0;
	wolf.player.pos.x = wolf.map.player_pos.x * 64 + 32;
	wolf.player.pos.y = wolf.map.player_pos.y * 64 + 32;
	wolf.player.angle = (M_PI / 2.0) * ((wolf.map.player_dir + 1) % 4);
	wolf.player.state = 0;
	wolf.player.speed = 10;
	wolf.player.strafe_speed = 6;
	wolf.player.hb = 16;
	if (state_loop(&wolf))
		return (1);
	return (wolf_quit(&wolf));
}
/*
__attribute__((destructor))
void end()
{
	while (1);
}
*/
